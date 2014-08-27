/* 
 * File:   GeneratedCases.cpp
 * Author: fernandofernandes
 * 
 * Created on 27 de Agosto de 2014, 18:44
 */

#include "GeneratedCases.h"
//melhor para pegar resultados variados

GeneratedCases::GeneratedCases(uint n, std::string t) {
    if (n <= 0 || m <= 0) {
        cerr << "(n || m) == 0\n";
        return;
    }
    this->tipo = t;
    this->n = n;
    this->m = m;
    this->dataVector = new int*[this->n];
}

GeneratedCases::GeneratedCases() {
    this->n = 0;
    this->m = 0;
    this->dataVector = NULL;
    this->tipo = "";
}

GeneratedCases::GeneratedCases(uint n, uint m) {
    if (n <= 0 || m <= 0) {
        cerr << "(n || m) == 0\n";
        return;
    }
    this->n = n;
    this->m = m;
    this->dataVector = new int*[this->n];
    if (this->dataVector != NULL)
        for (int i = 0; i < m; i++) {
            this->dataVector [i] = new int[this->m];
        }
}

GeneratedCases::GeneratedCases(const GeneratedCases& orig) {
}

GeneratedCases::~GeneratedCases() {
    if (this->n <= 0 || this->m)
        return;
    if (this->m > 0)
        for (int i = 0; i < m; i++) {
            delete [] this->dataVector [i];
        }
    delete [] this->dataVector;
}

int** GeneratedCases::GetDataVector() const {
    return dataVector;
}

void GeneratedCases::SetDataVector(int** dataVector) {
    this->dataVector = dataVector;
}

unsigned int GeneratedCases::GetM() const {
    return m;
}

void GeneratedCases::SetM(unsigned int m) {
    this->m = m;
}

unsigned int GeneratedCases::GetN() const {
    return n;
}

void GeneratedCases::SetN(unsigned int n) {
    this->n = n;
}

std::string GeneratedCases::GetTipo() const {
    return tipo;
}

void GeneratedCases::SetTipo(std::string tipo) {
    this->tipo = tipo;
}

void GeneratedCases::add(uint i, uint j, int dado) {
    if (i >= this->n || j >= this->m)
        return;
    this->dataVector[i][j] = dado;
}

int GeneratedCases::getAt(uint i, uint j) {
    if (i >= this->n || j >= this->m)
        return -1;
    return this->dataVector[i][j];
}

void GeneratedCases::mallocSizeM(uint sizeM) {
    if (this->dataVector != NULL)
        this->m = sizeM;
    for (uint i = 0; i < this->m; i++) {
        this->dataVector [i] = new int[this->m];
    }
}

void GeneratedCases::initData(uint n, string t) {
    if (n <= 0) {
        cerr << "(n || m) == 0\n";
        return;
    }
    this->tipo = t;
    this->n = n;
    this->dataVector = new int*[this->n];
}

int* GeneratedCases::getVet(uint i){
    if(this->n)
        return this->dataVector[i];
}