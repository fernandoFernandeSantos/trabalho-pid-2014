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
    CaseGenerator(uint n, uint m);
    CaseGenerator();
    CaseGenerator(uint n, string t);
    CaseGenerator(const CaseGenerator& orig);
    virtual ~CaseGenerator();
    int** GetDataVector() const;

    void SetDataVector(int** dataVector);
    
    Vetor GetM() const;

    void SetM(uint tam, uint pos);

    unsigned int GetN() const;

    void SetN(unsigned int n);

    std::string GetTipo() const;

    void SetTipo(std::string tipo);
    void add(uint i, uint j, int dado);
    int getAt(uint i, uint j);
    int* getVet(uint i);
    
    void mallocSizeM(uint posicao, int sizeM);
    void initData(uint n, string t);
    
    void Fscanf(string nome, uint i, uint k);
//    
//    static void geraRandomico(CaseGenerator *rand, string pasta);
//    static void geraSequencial(CaseGenerator *seq, string pasta);
//    static void geraInvertido(CaseGenerator *inv, string pasta);
//    

private:
    int **dataVector;
    unsigned int n; //quantidade de entradas
    Vetor m; // vetor de tamanhos

    std::string tipo; //pode ser invertido, randomico ou sequencial
};

#endif	/* GENERATEDCASES_H */

