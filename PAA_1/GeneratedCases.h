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
using namespace std;

class GeneratedCases {
public:
    GeneratedCases(uint n, uint m);
    GeneratedCases();
    GeneratedCases(uint n, string t);
    GeneratedCases(const GeneratedCases& orig);
    virtual ~GeneratedCases();
    int** GetDataVector() const;

    void SetDataVector(int** dataVector);
    unsigned int GetM() const;

    void SetM(unsigned int m);

    unsigned int GetN() const;

    void SetN(unsigned int n);

    std::string GetTipo() const;

    void SetTipo(std::string tipo);
    void add(uint i, uint j, int dado);
    int getAt(uint i, uint j);
    int* getVet(uint i);
    
    void mallocSizeM(uint sizeM);
    void initData(uint n, string t);

private:
    int **dataVector;
    unsigned int n; //quantidade de entradas
    unsigned int m; // quantidade de numeros

    std::string tipo; //pode ser invertido, randomico ou sequencial

};

#endif	/* GENERATEDCASES_H */

