#include <iostream>
#include <omp.h>
#include "functions.cpp"

using namespace std;
void time_test(double tam, AF dfa)
{
    string a = "b";
    for (int i = 0; i < tam - 3; i++)
        a.push_back('a');
    a.push_back('c');
    a.push_back('f');

    //double start_seq = omp_get_wtime();
    // bool res1 = verify_str(dfa, a);
    double start = omp_get_wtime();
    bool res = verify_parallel_string(dfa, a);
    double end = omp_get_wtime();

    printf("N° of threads: %d, string size: %d \n", omp_get_max_threads(), a.length());
    printf("Work took parallel %f miliseconds\n", (end - start) * 1000);
    //printf("Work took seq %f miliseconds\n", (start-start_seq)*1000);
    cout << "Result of verification: " << res << endl
         << endl;
}

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

    //Testing
    for (int i = 1; i < 10; i++)
    {
        time_test(pow(10, i), dfa);
    }

    return 0;
}
