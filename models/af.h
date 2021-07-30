#ifndef AF_H
#define AF_H

#include <unordered_map>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class AF
{
private:
    typedef unordered_map<int, unordered_map<char, vector<int>>> T;
    typedef vector<vector<int>> V;
    T transitions;
    V vertexs;
    vector<int> final_states;
    vector<bool> vis;

    void eclosure(int from, set<int> &result, vector<bool> &vis)
    {
        result.insert(from);

        for (int to : transitions[from]['^'])
        {
            if (!vis[to])
            {
                vis[to] = 1;
                eclosure(to, result, vis);
            }
        }
    }

public:
    AF() {}

    // Setea un conjunto de vertices secuenciales
    void set_vertex(int n_vertex)
    {
        for (int i = 0; i < n_vertex; i++)
        {
            vertexs.push_back({i});
        }
    }

    // Añade un vétice compuesto por otros vértices
    int add_vertex(vector<int> &vertex)
    {
        vertexs.push_back(vertex);
        vis.push_back(0);
        return vertexs.size() - 1;
    }

    vector<int> get_vertex(int index)
    {
        return vertexs[index];
    }

    void vis_vertex(int index)
    {
        vis[index] = 1;
    }

    int get_vertex_index(vector<int> &V)
    {
        for (int i = 0; i < vertexs.size(); i++)
        {
            if (V == vertexs[i])
                return i;
        }
        return -1;
    }

    int get_next_vertex_idx()
    {
        for (int i = 0; i < vis.size(); i++)
        {
            if (!vis[i])
                return i;
        }
        return -1;
    }

    V get_vertexs()
    {
        return vertexs;
    }

    int get_size_vertexs()
    {
        return vertexs.size();
    }

    void add_transition(int from, int to, char symbol)
    {
        transitions[from][symbol].push_back(to);
    }

    T get_transitions()
    {
        return transitions;
    }

    // Recibe vector con estados finales y los setea
    void set_final_state(vector<int> curr_final_states)
    {
        for (int i = 0; i < vertexs.size(); i++)
        {
            auto vertex = vertexs[i];
            for (int vertex_idx : vertex)
            {
                for (int final_state : curr_final_states)
                {
                    if (vertex_idx == final_state)
                    {
                        final_states.push_back(i);
                    }
                }
            }
        }
    }

    vector<int> get_final_states()
    {
        return final_states;
    }

    vector<char> get_reachable_symbols(const vector<int> &f_vertex)
    {
        set<char> result;

        for (int from : f_vertex)
        {
            for (auto trans : transitions[from])
            {
                if (trans.first != '^')
                {
                    result.insert(trans.first);
                }
            }
        }

        vector<char> V(result.begin(), result.end());

        return V;
    }

    vector<int> get_transition_vertex(const vector<int> &V, char symbol)
    {
        vector<int> result;

        for (int from : V)
        {
            for (int to : transitions[from][symbol])
            {
                result.push_back(to);
            }
        }

        return result;
    }

    vector<int> eclosure(const vector<int> &V)
    {
        set<int> result;
        vector<bool> vis(vertexs.size(), 0);

        for (int from : V)
        {
            eclosure(from, result, vis);
        }

        vector<int> v(result.begin(), result.end());

        return v;
    }

    void print()
    {
        for (auto from : transitions)
        {
            for (auto symbol : from.second)
            {
                for (int to : symbol.second)
                {
                    cout << "q" << from.first << " {";
                    for (int vertex_idx : vertexs[from.first])
                    {
                        cout << vertex_idx << ' ';
                    }
                    cout << "} -> q" << to << " {";
                    for (int vertex_idx : vertexs[to])
                    {
                        cout << vertex_idx << ' ';
                    }
                    cout << "} : Symbol - " << symbol.first << '\n';
                }
            }
        }
    }

    ~AF() {}
};

#endif
