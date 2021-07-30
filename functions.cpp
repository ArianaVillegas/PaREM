#include <vector>
#include <stack>
#include <algorithm>
#include <omp.h>
#include <math.h>
#include "models/af.h"
#include "models/Regx.cpp"
#include "models/operators.cpp"

#define n_threads 4

using namespace std;

AF re_to_nfa(string re)
{
    auto reg = RegExParser(re);
    auto ast_nodes = reg.postorder();
    stack<AF> nfa_nodes;
    while (!ast_nodes.empty())
    {
        auto ast_node = ast_nodes.top();
        ast_nodes.pop();

        if (ast_node == "conc")
        {
            auto right_nfa = nfa_nodes.top();
            nfa_nodes.pop();
            auto left_nfa = nfa_nodes.top();
            nfa_nodes.pop();

            vector<AF> ops;
            ops.push_back(left_nfa);
            ops.push_back(right_nfa);

            nfa_nodes.push(concat_operator(ops));
        }
        else if (ast_node == "*")
        {
            auto cur_nfa = nfa_nodes.top();
            nfa_nodes.pop();
            cur_nfa.add_transition(0, cur_nfa.get_size_vertexs() - 1, '^');
            cur_nfa.add_transition(cur_nfa.get_size_vertexs() - 1, 0, '^');
            nfa_nodes.push(cur_nfa);
        }
        else if (ast_node == "|")
        {
            auto right_nfa = nfa_nodes.top();
            nfa_nodes.pop();
            auto left_nfa = nfa_nodes.top();
            nfa_nodes.pop();

            vector<AF> ops;
            ops.push_back(left_nfa);
            ops.push_back(right_nfa);

            nfa_nodes.push(or_operator(ops));
        }
        else if (ast_node == "+")
        {
            auto cur_nfa = nfa_nodes.top();
            nfa_nodes.pop();
            cur_nfa.add_transition(cur_nfa.get_size_vertexs() - 1, 0, '^');
            nfa_nodes.push(cur_nfa);
        }
        else if (ast_node == "?")
        {
            auto cur_nfa = nfa_nodes.top();
            nfa_nodes.pop();
            cur_nfa.add_transition(0, cur_nfa.get_size_vertexs() - 1, '^');
            nfa_nodes.push(cur_nfa);
        }
        else
        {
            AF *nfa_node = new AF();
            nfa_node->set_vertex(2);
            nfa_node->set_final_state({1});
            nfa_node->add_transition(0, 1, ast_node[0]);
            nfa_nodes.push(*nfa_node);
        }
    }

    return nfa_nodes.top();
}

AF nfa_to_dfa(AF nfa)
{
    AF dfa;

    vector<int> start_states = nfa.eclosure({0});

    int from = dfa.add_vertex(start_states);

    while (from != -1)
    {
        vector<int> V = dfa.get_vertex(from);
        dfa.vis_vertex(from);

        vector<char> symbols = nfa.get_reachable_symbols(V);
        for (char symbol : symbols)
        {
            vector<int> eclosure = nfa.eclosure(nfa.get_transition_vertex(V, symbol));

            if (eclosure.empty())
                continue;

            int to = dfa.get_vertex_index(eclosure);
            if (to == -1)
            {
                to = dfa.add_vertex(eclosure);
            }
            dfa.add_transition(from, to, symbol);
        }
        from = dfa.get_next_vertex_idx();
    }

    dfa.set_final_state(nfa.get_final_states());

    return dfa;
}

bool verify_str(AF dfa, string str)
{
    vector<vector<vector<int>>> I(n_threads);
    auto transitions = dfa.get_transitions();
    auto final_states = dfa.get_final_states();

    for (int i = 0; i < n_threads; i++)
    {
        int start = i * floor(str.size() * 1.0 / n_threads);
        int end = (i != n_threads - 1) ? (i + 1) * floor(str.size() * 1.0 / n_threads) : (str.size() * 1.0);
        vector<int> S, L, R;
        for (auto itr : transitions)
        {
            if (itr.second[str[start]].empty() == false)
                S.push_back(itr.first);
            if (i && itr.second[str[start - 1]].empty() == false)
                L.push_back(itr.second[str[start - 1]][0]);
            else
                L.push_back(0);
        }

        sort(S.begin(), S.end());
        sort(L.begin(), L.end());
        set_intersection(S.begin(), S.end(), L.begin(), L.end(), back_inserter(R));

        for (int vertix_idx : R)
        {
            vector<int> Rr;
            for (int i = start; i < end; i++)
            {
                Rr.push_back(vertix_idx);
                vertix_idx = transitions[vertix_idx][str[i]][0];
            }
            Rr.push_back(vertix_idx);
            I[i].push_back(Rr);
        }
    }

    if (str.size() >= n_threads && I.front().empty())
    {
        return 0;
    }

    bool f_state = 0;
    for (auto Rr : I.back())
    {
        if (find(final_states.begin(), final_states.end(), Rr.back()) != final_states.end())
        {
            f_state = 1;
            break;
        }
    }
    if (!f_state)
        return 0;

    int cur = I.front().front().back();
    for (int i = 1; i < n_threads; i++)
    {
        int start = i * floor(str.size() * 1.0 / n_threads);
        int end = (i != n_threads - 1) ? (i + 1) * floor(str.size() * 1.0 / n_threads) : (str.size() * 1.0);

        bool f_step = 0;

        if (I[i].empty())
            return 0;

        for (auto Rr : I[i])
        {
            if (cur == Rr.front() && Rr.size() == end - start + 1)
            {
                f_step = 1;
                cur = Rr.back();
                break;
            }
        }
        if (!f_step)
            return 0;
    }

    return 1;
}