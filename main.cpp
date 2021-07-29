#include <iostream>
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

    AF nfa = re_to_nfa("b?c|a*cf");
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

    bool res = verify_str(dfa, "baaaacf");

    cout << "Result of verification: " << res << '\n';

    return 0;
}