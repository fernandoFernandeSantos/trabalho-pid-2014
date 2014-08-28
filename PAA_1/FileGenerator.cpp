/* 
 * File:   FileGenerator.cpp
 * Author: familia
 * 
 * Created on 10 de Agosto de 2014, 16:29
 */

#include "FileGenerator.h"


using namespace std;

FileGenerator::FileGenerator() {
}

FileGenerator::FileGenerator(const FileGenerator& orig) {
}

FileGenerator::~FileGenerator() {
}
/*
void FileGenerator::worst_for_selection(int valor[], int tamanho) {

    int aux = valor[0];

    for (int i = 1; i < tamanho - 1; i++) {
        valor[i] = valor[i + 1];
    }
    valor[tamanho - 1] = aux;
}

void FileGenerator::sort(int valor[], int esquerda, int direita) {
    int i, j, x, y;

    i = esquerda;
    j = direita;
    x = valor[(esquerda + direita) / 2];

    while(i <= j){
        while(valor[i] < x && i < direita){
            i++;
        }

        while(valor[j] > x && j > esquerda){
            j--;
        }

        if(i <= j){
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }

    if(i < direita){
        sort(valor, i, direita);
    }

    if(j > esquerda){
        sort(valor, esquerda, j);
    }
}

void FileGenerator::inverte(int v[], int fim) {
       int j = fim - 1;
    for(int i = 0; i < fim/2; i++){
        int aux = v[j];
        v[j] = v[i];
        v[i] = aux;
        j--;
    }
}
*/
int FileGenerator::generate(string pasta) {
    string pastaSaida = "cd "+ pasta;
    if(system(pastaSaida.c_str())){
        cout << "Criando pasta\n";
        string foi = "mkdir "+pasta;
        system(foi.c_str());
        pasta = "cd "+pasta;
        system(pasta.c_str());
    }
    
    ofstream output;
    ostringstream outputstring;
    srand( (unsigned)time(0));
    //randomico
    for(int j = 1 ; j <= 6; j++){

        int limit  = 10000;

        while(limit <= 100000){
            outputstring << pasta + "/arq" << limit << "n" << j << ".txt";
            string s = outputstring.str();
            cout << s << endl;
            output.open(s.c_str());
            outputstring.str("");
            outputstring.clear();


            for(int i = 0; i < limit; i++){
                output << rand() << endl;
            }
            output.close();

            limit += 5000;
        } //fim while limit

    } //fim for randomico
    outputstring.str("");
    outputstring.clear();
    
    //sequencial
    for(int i = 1; i <= 2; i++){
        int limit = 10000;
        while(limit <= 100000){

            //int vetor[limit];

            outputstring << pasta + "/arq" << limit << "seq" << "n" << i << ".txt";

            string s = outputstring.str();
            cout << s << endl;
            output.open(s.c_str());
            outputstring.str("");
            outputstring.clear();

            /*for(int j = 0; j < limit; j++){
                vetor[j] = rand();
            }
            sort(vetor, 0, limit - 1);
             */

            for(int j = 0; j < limit; j++){
                output << j << endl;
            }
            limit += 5000;

            output.close();
        }
    }

    //inverso - pior caso
    outputstring.str("");
    outputstring.clear();
    
    for(int i = 1; i <= 2; i++){

        int limit = 10000;
        while(limit <= 100000){

            //int vetor[limit];

            outputstring << pasta + "/arq" << limit << "inv" << "n" << i << ".txt";

            string s = outputstring.str();
            cout << s << endl;
            output.open(s.c_str());
            outputstring.str("");
            outputstring.clear();
            /*
            for(int j = 0; j < limit; j++){
                vetor[j] = rand();
            }
            sort(vetor, 0, limit - 1);
            inverte(vetor, limit);
             */
            //salva invertido
            for(int j = limit - 1; j >= 0; j--)
                output << j << endl;


            limit += 5000;
            output.close();
        }
    }
}

