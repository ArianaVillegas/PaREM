#include <vector>
#include <algorithm>
#include <omp.h>
#include <math.h>
#include "af.h"

//#define n_threads 4

using namespace std;

AF or_operator(vector<AF> ops)
{
    AF result;
    int size = 2;

    for (auto af : ops)
        size += af.get_size_vertexs();

    result.set_vertex(size);

    int base = 1;
    for (auto af : ops)
    {
        result.add_transition(0, base, '^');
        for (auto from : af.get_transitions())
        {
            for (auto symbol : from.second)
            {
                for (auto to : symbol.second)
                {
                    result.add_transition(base + from.first, base + to, symbol.first);
                }
            }
        }
        base += af.get_size_vertexs();
        result.add_transition(base - 1, size - 1, '^');
    }

    result.set_final_state({size - 1});

    return result;
}

AF concat_operator(vector<AF> ops)
{
    AF result;
    int size = 2;

    for (auto af : ops)
        size += af.get_size_vertexs();

    result.set_vertex(size);

    int base = 1;
    for (auto af : ops)
    {
        if (base == 1)
            result.add_transition(0, base, '^');
        for (auto from : af.get_transitions())
        {
            for (auto symbol : from.second)
            {
                for (auto to : symbol.second)
                {
                    result.add_transition(base + from.first, base + to, symbol.first);
                }
            }
        }
        base += af.get_size_vertexs();
        result.add_transition(base - 1, base, '^');
    }

    result.set_final_state({size - 1});

    return result;
}