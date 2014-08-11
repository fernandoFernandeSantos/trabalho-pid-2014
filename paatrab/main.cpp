/* 
 * File:   main.cpp
 * Author: familia
 *
 * Created on 10 de Agosto de 2014, 16:27
 */

#include <cstdlib>
#include "FileGenerator.h"
#include <iostream>
#include "Vetor.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "\n\n\n\t\tAlgoritmos de Ordenação como Métodos de Classe\n\n\n";
    cout << "Quantos elementos deve ter o vetor? > ";
    int n = 0;
    cin >> n;
    cin.get();
    cout << "Criando um vetor de inteiros aleatório de tamanho " << n << ".\n";
    Vetor V(n);
    
    for (int i = 0; i < n; i++) {
        V[i] = rand() % (2 * n);
        cout << ".";
    }
    cout << "\nVetor criado: \n";
    V.escreve();
    cout << endl;
    cout << "Ordenando vetor com insertion().\n";
    V.QuickSort(V.getVetor(), 0, n -1);
    V.escreve();
    cout << endl;
    return 0;
}

