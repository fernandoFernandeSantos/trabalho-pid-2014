/* 
 * File:   GeneratedCases.cpp
 * Author: fernandofernandes
 * 
 * Created on 27 de Agosto de 2014, 18:44
 */

#include "CaseGenerator.h"
//melhor para pegar resultados variados

CaseGenerator::CaseGenerator(uint n, std::string t) {
    if (n <= 0) {
        cerr << "(n || m) == 0\n";
        return;
    }
    this->tipo = t;
    this->n = n;

    this->dataVector = new int*[this->n];
}

CaseGenerator::CaseGenerator() {
    this->n = 0;
    this->m = 0;
    this->dataVector = NULL;
    this->tipo = "";
}

CaseGenerator::CaseGenerator(const CaseGenerator& orig) {
}

CaseGenerator::~CaseGenerator() {
    if (this->n <= 0)
        return;
    for (int i = 0; i < this->n; i++) {
        delete [] this->dataVector [i];
    }
    delete [] this->dataVector;
}

int** CaseGenerator::GetDataVector() const {
    return dataVector;
}

void CaseGenerator::SetDataVector(int** dataVector) {
    this->dataVector = dataVector;
}

Vetor CaseGenerator::GetM() const {
    return m;
}

void CaseGenerator::SetM(uint tam, uint pos) {
    this->m[pos] = tam;
}

unsigned int CaseGenerator::GetN() const {
    return n;
}

void CaseGenerator::SetN(unsigned int n) {
    this->n = n;
}

std::string CaseGenerator::GetTipo() const {
    return tipo;
}

void CaseGenerator::SetTipo(std::string tipo) {
    this->tipo = tipo;
}

void CaseGenerator::mallocSizeM(uint posicao, int sizeM) {
    if (this->dataVector != NULL) {
        this->m[posicao] = sizeM;
        for (uint i = 0; i < this->m[posicao]; i++) {
            this->dataVector [i] = new int[this->m[posicao]];
        }
    }
}

void CaseGenerator::initData(uint n, string t) {
    if (n <= 0) {
        cerr << "(n || m) == 0\n";
        return;
    }
    this->tipo = t;
    this->n = n;
    this->dataVector = new int*[this->n];
}

int* CaseGenerator::getVet(uint i) {
    if (this->n)
        return this->dataVector[i];
}

void CaseGenerator::Fscanf(string nome, uint i, uint k) {

    std::ifstream ifs;
    ifs.open(nome.c_str());
    cout << nome << endl;
    if (ifs.fail()) {
        cout << "Falha ao abrir o arquivo\nTente mudar o diretório do executável na função principal";
        exit(1);
    }

    if (i < 0 || i >= this->n || this->m[k] <= 0 || this->n <= 0) return;

    if (this->dataVector[i] != NULL) {
        delete[] this->dataVector[i];
    }
    this->dataVector[i] = new int[this->m[k]];
    for (uint j = 0; j < this->m[k]; j++) {
        ifs >> this->dataVector[i][j];
    }
    ifs.close();

}
