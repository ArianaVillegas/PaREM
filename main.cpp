#include <iostream>
#include "functions.cpp"

using namespace std;

int main()
{
    AF nfa = re_to_nfa("b?(c|a*cf)");
    /*nfa.print();
    auto f_st = nfa.get_final_states();
    cout << "Final states: ";
    for (auto x : f_st)
    {
        cout << x << ' ';
    }
    cout << '\n';*/

    AF dfa = nfa_to_dfa(nfa);
    dfa.print();
    auto f_st = dfa.get_final_states();
    cout << "Final states: ";
    for (auto x : f_st)
    {
        cout << x << ' ';
    }
    cout << '\n';

    bool res = verify_str(dfa, "bccf");

    cout << "Result of verification: " << res << '\n';

    return 0;
}