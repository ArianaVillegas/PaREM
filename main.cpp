#include <iostream>
#include <omp.h>
#include "Test.cpp"

using namespace std;








int main()
{
    //Direct Call
    /*
    AF nfa = re_to_nfa("b?c|a*cf");
    AF dfa = nfa_to_dfa(nfa);
    
    string str = "b";
    for(int i = 0;i<99999997;i++)
        str.push_back('a');
    str.push_back('c');
    str.push_back('f');
    
    string str = "bacf";
    //paralelo
    bool res = verify_parallel_string(dfa, str,10);
    //serial
    bool res = verify_str(dfa, str);
    cout<<res<<endl;
    */
    string RegExpresion = "b?c|a*cf";
    string word;
    /*
    string word = "b";
    for(int i = 0;i<99999997;i++)
        word.push_back('a');
    word.push_back('c');
    word.push_back('f');
    */
    word = "bacf";
    Test testing = Test(word,RegExpresion);
    testing.set_threads(10);
    testing.getTime_exec();
    testing.getTime_seq();
    return 0;
}
