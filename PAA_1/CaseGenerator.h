/* 
 * File:   GeneratedCases.h
 * Author: fernandofernandes
 *
 * Created on 27 de Agosto de 2014, 18:44
 */


#ifndef GENERATEDCASES_H
#define	GENERATEDCASES_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <sstream>
#include "Vetor.h"
using namespace std;

class CaseGenerator {
public:

    CaseGenerator() {
        this->n = 0;
        for (int i = 0; i < this->n; i++) {
            this->sizes [i] = 0;
            this->dataVector[i] = NULL;
        }
        this->tipo = "";
    }

    ~CaseGenerator() {
        if (this->n <= 0)
            return;
        for (int i = 0; i < this->n; i++) {
            delete [] this->dataVector[i];
        }
        delete [] this->dataVector;
    }

    bool Malloc(string tipo) {
        if (this->n <= 0) return false;
        this->tipo = tipo;
        this->dataVector = new int*[this->n];
    }

    uint GetN() {
        return this->n;
    }

    void SetN(uint n) {
        this->n = n;
    }

    void SetSizes(uint posSize, uint valor) {
        this->sizes[posSize] = valor;
    }

    void Fscanf(string nome, uint posVet, uint tamanho) {

        std::ifstream ifs;
        ifs.open(nome.c_str());
        cout << nome << endl;
        if (ifs.fail()) {
            cout << "Falha ao abrir o arquivo\nTente mudar o diretório do executável na função principal";
            exit(1);
        }

        if (posVet < 0 || posVet >= this->n || posVet >= this->n || this->n <= 0) return;

        if (this->dataVector[posVet] != NULL) {
            delete[] this->dataVector[posVet];
        }
        this->dataVector[posVet] = new int[tamanho];
        for (uint j = 0; j < tamanho; j++) {
            ifs >> this->dataVector[posVet][j];
        }
        ifs.close();

    }

    int* GetVetor(uint posVet) {
        if (posVet >= this->n) return NULL;
        return this->dataVector[posVet];
    }

    uint GetSizeAt(uint posSize) {
        return this->sizes[posSize];
    }

    static void geraRandomico(CaseGenerator rand[], string pasta) {
        uint posSize = 0;
        std::ostringstream inputstring;
        string s = "";
        for (int i = 0; i < 6; i++) {
            int limit = 10000;
            while (limit <= 100000) {
                inputstring << pasta + "/arq" << limit << "n" << (i + 1) << ".txt";
                s = inputstring.str();
                rand[i].SetSizes(posSize, limit); //coloca o tamanho do vetor na posição i
                rand[i].Fscanf(s, posSize, limit);
                limit += 5000;
                posSize++;
                inputstring.str("");
                s.clear();
            } //fim while limit
            posSize = 0;
        } //fim for randomico
    }

    static void geraSequencial(CaseGenerator seq[], string pasta) {
        std::ostringstream inputstring;
        string s = "";
        uint posSize = 0;
        for (int i = 0; i < 2; i++) {
            int limit = 10000;
            while (limit <= 100000) {
                inputstring << pasta + "/arq" << limit << "seq" << "n" << (i + 1) << ".txt";
                s = inputstring.str();
                seq[i].SetSizes(posSize, limit); //coloca o tamanho do vetor na posição i
                seq[i].Fscanf(s, posSize, limit);
                inputstring.str("");
                inputstring.clear();
                limit += 5000;
                s.clear();
                posSize++;
            }
            posSize = 0;
        }
    }

    static void geraInvertido(CaseGenerator inv[], string pasta) {
        std::ostringstream inputstring;
        string s = "";
        uint posSize = 0;
        for (int i = 0; i < 2; i++) {
            int limit = 10000;
            while (limit <= 100000) {
                inputstring << pasta + "/arq" << limit << "inv" << "n" << (i + 1) << ".txt";
                s = inputstring.str();
                inv[i].SetSizes(posSize, limit); //coloca o tamanho do vetor na posição i
                inv[i].Fscanf(s, posSize, limit);
                posSize++;
                inputstring.str("");
                inputstring.clear();
                limit += 5000;
                s.clear();
            }
            posSize = 0;
        }
    }
private:
    int** dataVector;
    int sizes[20]; // vetor de tamanhos
    unsigned int n; //quantidade de entradas
    std::string tipo; //pode ser invertido, randomico ou sequencial
};

#endif	/* GENERATEDCASES_H */

