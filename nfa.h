#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include "defs.h"

using namespace std;

class NFA
{
private:
    unordered_map<int, unordered_map<char, vector<int>>> transitions;
    vector<vector<int>> vertexs;
    vector<int> final_states;

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
    NFA() {}

    void set_vertex(int n_vertex)
    {
        for (int i = 0; i < n_vertex; i++)
        {
            vertexs.push_back({i});
        }
    }

    vector<vector<int>> get_vertexs()
    {
        return vertexs;
    }

    void add_transition(int from, int to, char symbol)
    {
        transitions[from][symbol].push_back(to);
    }

    void set_final_state(int new_final_state)
    {
        final_states.push_back(new_final_state);
    }

    vector<int> get_final_state()
    {
        return final_states;
    }

    int get_size_vertexs()
    {
        return vertexs.size();
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
            for (auto trans : from.second)
            {
                for (int to : trans.second)
                {
                    cout << from.first << " -> " << to << " symbol - " << trans.first << '\n';
                }
            }
        }
    }

    ~NFA() {}
};

#endif
