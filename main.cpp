#include <iostream>
#include <omp.h>
#include "functions.cpp"

using namespace std;
int MAX_THREADS = 10;

// Tamaño de sting 10^N
int FACTOR_STRING = 8;


void time_test(double tam,AF dfa){
    
    string a = "b";
    for(int i = 0;i<tam-3;i++)
        a.push_back('a');
    a.push_back('c');
    a.push_back('f');
    
    //double start_seq = omp_get_wtime();
   // bool res1 = verify_str(dfa, a);
    double start = omp_get_wtime();
    bool res = verify_parallel_string(dfa, a,4);
    double end= omp_get_wtime();

    printf("N° of threads: %d, string size: %d \n",omp_get_max_threads(),a.length());
    printf("Work took parallel %f miliseconds\n", (end - start)*1000);
    //printf("Work took seq %f miliseconds\n", (start-start_seq)*1000);
    cout << "Result of verification: " << res << endl<<endl;
}


void runTest(double tam, AF &dfa)
{
  // Generamos el string a validar de tamaño tam
  string a = "b";
  for(int i = 0;i<tam-3;i++)
      a.push_back('a');
  a.push_back('c');
  a.push_back('f');

  double start_seq = omp_get_wtime();
  bool res1 = verify_str(dfa, a);
  double start = omp_get_wtime();
  double serialTime = start-start_seq;

  // Declaramos nuestro archivo de data
  FILE *dataFile;

  if ((int) log10(tam) == 1)
    // Abrimos nuestro archivo de data set en write
    dataFile = fopen("dataFile.dat", "w");
  else
    // Abrimos nuestro archivo de data set en append
    dataFile = fopen("dataFile.dat", "a");

  if (dataFile == NULL)
  {
    printf("Could not open file");
  }

  // Guardamos el tiempo secuencial
  fprintf(dataFile, "\"String 10^%d\"\n", (int) log10(tam));
  //nProcesos tiempo
  fprintf(dataFile, "1 %f\n", serialTime/serialTime);

  for (size_t i = 2; i <= MAX_THREADS; i++) {
    // Definimos el número de hilos
    //omp_set_num_threads(i);
    start = omp_get_wtime();
    bool res = verify_parallel_string(dfa, a,i);
    double end= omp_get_wtime();
    double parallelTime = end-start;

    //nProceso tiempoParalelo
    fprintf(dataFile, "%lu %f\n", i, serialTime/parallelTime);
    cout << "Result of verification: " << res << '\n';
  }

  if ((int) log10(tam) != FACTOR_STRING)
    fprintf(dataFile, "\n\n");

   //Cerramos nuestro archivo de data set
   fclose(dataFile);

   // //Separamos el set de data
   // fprintf(dataFile,"\n\n");
   //
   // // Guardamos el tiempo paralelo
   // fprintf(dataFile, "Verificación paralela\n");
}

void runNTest(AF &dfa)
{
  // Testing
  for(int i = 1; i<=FACTOR_STRING;i++){
      runTest(pow(10,i),dfa);
  }
}

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

    //Testing
    /*
    for(int i = 1;i<3;i++){
        time_test(pow(10,i),dfa);
    }*/
    
    string str = "bacf";
    bool res = verify_parallel_string(dfa, str,10);
    //bool res = verify_str(dfa, str);
    cout<<res<<endl;
    
    //runNTest(dfa);
    return 0;
}
