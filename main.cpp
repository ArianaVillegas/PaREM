#include <iostream>
#include <omp.h>
#include "functions.cpp"

using namespace std;

int main()
{
    /*AF nfa;
    nfa.set_vertex(4);
    nfa.set_final_state({3});
    nfa.add_transition(0, 0, 'a');
    nfa.add_transition(0, 1, 'a');
    nfa.add_transition(0, 2, 'b');
    nfa.add_transition(1, 1, 'b');
    nfa.add_transition(1, 3, 'b');
    nfa.add_transition(1, 3, '^');
    nfa.add_transition(2, 2, 'a');
    nfa.add_transition(2, 2, 'b');
    nfa.add_transition(2, 3, 'a');*/

    /*nfa.print();
    auto f_st = nfa.get_final_states();
    cout << "Final states: ";
    for (auto x : f_st)
    {
        cout << x << ' ';
    }
    cout << '\n';*/

    AF dfa = nfa_to_dfa(nfa);
    /*dfa.print();
    auto f_st = dfa.get_final_states();
    cout << "Final states: ";
    for (auto x : f_st)
    {
        cout << x << ' ';
    }
    cout << '\n';*/
    string a = "b";
    for(int i = 0;i<99999997;i++)
        a.push_back('a');
    a.push_back('c');
    a.push_back('f');
    
    double start_seq = omp_get_wtime();
    bool res1 = verify_str(dfa, a);
    double start = omp_get_wtime();
    bool res = verify_parallel_string(dfa, a);
   
    double end= omp_get_wtime();
   
    printf("Work took parallel %f seconds\n", end - start);
    printf("Work took seq %f seconds\n", start-start_seq);
    cout << "Result of verification: " << res << '\n';

    return 0;
}
