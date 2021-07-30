
#ifndef TEST_H
#define TEST_H

#include <string>
#include "functions.cpp"
class Test{
    private:
        int num_threads;
        std::string RegExpresion;
        std::string TestWord;

        AF nfa;
        AF dfa;


    public:
        Test(std::string word,std::string reg){
            RegExpresion = reg;
            TestWord=word;
            nfa = re_to_nfa(RegExpresion);
            dfa = nfa_to_dfa(nfa);
        }
        void set_threads(int n){
            num_threads = n;
        }
        void getTime_exec(){
            double start = omp_get_wtime();
            bool res = verify_parallel_string(dfa, TestWord,num_threads);
            double end= omp_get_wtime();
            cout<<"RegExpression: "<<RegExpresion<<"  Word to test:"<<TestWord<<endl;
            printf("N° of threads: %d, string size: %d \n",omp_get_max_threads(),TestWord.length());
            printf("Work took parallel %f miliseconds\n", (end - start)*1000);
            cout << "Result of verification: " << res << endl<<endl;
        }
        void getTime_seq(){
            double start = omp_get_wtime();
            bool res = verify_str(dfa, TestWord);
            double end= omp_get_wtime();

            cout<<"RegExpression: "<<RegExpresion<<"  Word to test:"<<TestWord<<endl;
            printf("Ejecución secuencial completada\n");
            printf("Work took seq %f miliseconds\n", (end - start)*1000);
            cout << "Result of verification: " << res << endl<<endl;
        }


        void generate_word(int tam){
            TestWord = "b";
            for(int i = 0;i<tam-3;i++)
                TestWord.push_back('a');
            TestWord.push_back('c');
            TestWord.push_back('f');
        }

        void runTest(double tam, int max_threads, int fact_string)
        {
            // Generamos el string a validar de tamaño tam
            string a = TestWord;

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

            for (size_t i = 2; i <= max_threads; i++) {
                // Definimos el número de hilos
                start = omp_get_wtime();
                bool res = verify_parallel_string(dfa, a,i);
                double end= omp_get_wtime();
                double parallelTime = end-start;

                //nProceso tiempoParalelo
                fprintf(dataFile, "%lu %f\n", i, serialTime/parallelTime);
                cout << "Result of verification: " << res << '\n';
            }   

            if ((int) log10(tam) != fact_string)
                fprintf(dataFile, "\n\n");

            //Cerramos nuestro archivo de data set
            fclose(dataFile);

            // //Separamos el set de data
            // fprintf(dataFile,"\n\n");
            //
            // // Guardamos el tiempo paralelo
            // fprintf(dataFile, "Verificación paralela\n");
            }


        //Crear el datafile a ser dibujado
        void runNTest(int tam,int max_threads)
        {
            int fact_string=log10(tam);
            for(int i = 1; i<=fact_string;i++){
                runTest(pow(10,i),max_threads,fact_string);
            }
        }





};

#endif