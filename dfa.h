#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <vector>
#include "defs.h"

using namespace std;

class DFA
{
private:
    typedef unordered_map<int, unordered_map<char, vector<int>>> T;
    T transitions;
    vector<vector<int>> vertexs;
    vector<int> final_states;
    vector<bool> vis;

public:
    DFA() {}

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

    void add_transition(int from, int to, char symbol)
    {
        transitions[from][symbol].push_back(to);
    }

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

    int get_next_vertex_idx()
    {
        for (int i = 0; i < vis.size(); i++)
        {
            if (!vis[i])
                return i;
        }
        return -1;
    }

    T get_transitions()
    {
        return transitions;
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

    ~DFA() {}
};

#endif
