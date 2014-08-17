/* 
 * File:   FileGenerator.cpp
 * Author: familia
 * 
 * Created on 10 de Agosto de 2014, 16:29
 */

#include "FileGenerator.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
klkç

using namespace std;

FileGenerator::FileGenerator() {
}

FileGenerator::FileGenerator(const FileGenerator& orig) {
}

FileGenerator::~FileGenerator() {
}

void worst_for_selection(int valor[], int tamanho) {

    int aux = valor[0];

    for (int i = 1; i < tamanho - 1; i++) {
        valor[i] = valor[i + 1];
    }
    valor[tamanho - 1] = aux;
}

void sort(int valor[], int esquerda, int direita) {
    int i, j, x, y;

    i = esquerda;
    j = direita;
    x = valor[(esquerda + direita) / 2];

    while (i <= j) {
        while (valor[i] < x && i < direita) {
            i++;
        }

        while (valor[j] > x && j > esquerda) {
            j--;
        }

        if (i <= j) {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }

    if (i < direita) {
        sort(valor, i, direita);
    }

    if (j > esquerda) {
        sort(valor, esquerda, j);
    }
}

void inverte(int v[], int fim) {
    int j = fim - 1;
    for (int i = 0; i < fim / 2; i++) {
        int aux = v[j];
        v[j] = v[i];
        v[i] = aux;
        j--;
    }
}

int FileGenerator::generate() {
    try {
        ofstream a;
        ostringstream oss;
        srand((unsigned) time(0));
        //loucura (só rand)
        for (int j = 1; j <= 6; j++) {

            int limit = 10000;

            while (limit <= 100000) {

                oss << "arq" << limit << "n" << j << ".txt";
                string s = oss.str();
                cout << s << endl;
                a.open(s.c_str());
                oss.str("");
                oss.clear();


                for (int i = 0; i < limit; i++) {
                    a << rand() << endl;
                }
                a.close();

                limit += 5000;
            }

        }
        oss.str("");
        oss.clear();
        
        //ordenado
        for (int i = 1; i <= 2; i++) {
            int limit = 10000;
            while (limit <= 100000) {

                int vetor[limit];

                oss << "arq" << limit << "seq" << "n" << i << ".txt";

                string s = oss.str();
                cout << s << endl;
                a.open(s.c_str());
                oss.str("");
                oss.clear();

                for (int j = 0; j < limit; j++) {
                    vetor[j] = rand();
                }
                sort(vetor, 0, limit - 1);


                for (int j = 0; j < limit; j++) {
                    a << vetor[j] << endl;
                }
                limit += 5000;

                a.close();
            }
        }

        //inverso - pior caso
        oss.str("");
        oss.clear();
        for (int i = 1; i <= 2; i++) {

            int limit = 10000;
            while (limit <= 100000) {

                int vetor[limit];

                oss << "arq" << limit << "inv" << "n" << i << ".txt";

                string s = oss.str();
                cout << s << endl;
                a.open(s.c_str());
                oss.str("");
                oss.clear();

                for (int j = 0; j < limit; j++) {
                    vetor[j] = rand();
                }
                sort(vetor, 0, limit - 1);
                inverte(vetor, limit);

                //salva invertido
                for (int j = 0; j < limit; j++)
                    a << vetor[j] << endl;
                a.close();

                //deisverte
                inverte(vetor, limit);
                //bota no pior pro selction
                worst_for_selection(vetor, limit);

                oss << "arq" << limit << "seln" << i << ".txt";
                cout << oss.str() << endl;
                a.open(oss.str().c_str());
                oss.str("");
                oss.clear();

                for (int j = 0; j < limit; j++)
                    a << vetor[j] << endl;

                limit += 5000;
                a.close();
            }
        }
        return 1;
    } catch (ifstream::failure e) {
        cout << e.what() << endl;
        return -1;
    }

}