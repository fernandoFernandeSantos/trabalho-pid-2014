/* 
 * File:   Vetor.cpp
 * Author: alunos
 * 
 * Created on 31 de Julho de 2014, 10:38
 */

#include "Vetor.h"
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;
// Implementação dos métodos da classe Vetor

Vetor::Vetor() {
    // construtor default
    cout << "Construtor default construindo vetor...\n";
    n = 0;
    V = NULL;
    cout << "Vetor construido.\n";
}

Vetor::Vetor(int tam) {
    cout << "Construtor inicializável construindo vetor...\n";
    if (tam < 0) {
        cerr << "Erro: o número de elementos não pode ser negativo.\n";
        cerr << "Ajustando número de elementos para zero.\n";
        n = 0;
        V = NULL;
    } else {
        n = tam;
        V = new int[n];
        if (V == NULL) {
            cerr << "Erro 1: Não é possível construir um vetor com tamanho\n ";
            cerr << n << ".";
            exit(1);
        } else {
            for (int i = 0; i < n; i++)
                V[i] = 0;
        }
    }
    cout << "Vetor construído\n";
}


Vetor::Vetor(const Vetor &A) {
    cout << "Construtor de cópia construindo Vetor...\n";
    this->n = A.n;
    V = new int[this->n];
    if (V == NULL) {
        cerr << "Erro 2: Não é possível criar a cópia do vetor.";
        exit(2);
    }
    for (int i = 0; i < this->n; i++) {
        this->V[i] = A.V[i];
    }
    cout << "Vetor construído.";
}

Vetor::~Vetor() {
    cout << "Destruindo Vetor...\n";
    delete[] V;
    cout << "Vetor destruído\n";
}

void Vetor::realloc() {
    if (n == 0) // Não há elementos no vetor;
    {
        V = new int[++n];
        if (V == NULL) // Alocação falhou
        {
            cerr << "Erro 3: Não é possível redimensionar o vetor.";
            exit(3);
        }
    } else {
        int *aux = new int[n];
        if (aux == NULL) {
            cerr << "Erro 3: Não é possível redimensionar o vetor.";
            exit(3);
        }
        for (int i = 0; i < (n); i++)
            aux[i] = V[i];
        delete[] V;
        V = new int [++n];
        if (V == NULL) {
            cerr << "Erro 3: Não é possível redimensionar o vetor.";
            exit(3);
        }
        for (int i = 0; i < (n - 1); i++)
            V[i] = aux[i];
        V[n - 1] = 0;
        delete[] aux;
    }
    return;
}

void Vetor::add(int valor) {
    realloc();
    V[n - 1] = valor;
    return;
}

int Vetor::get(int i) {
    if ((i < 0) || (i > n)) {
        cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
        return 0;
    } else {
        return V[i];
    }
}

int Vetor::getTamanho() {
    return this->n;
}

void Vetor::set(int i, int v) {
    if ((i < 0) || (i > n)) {
        cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
        cerr << "Atribuição abortada.\n";
        return;
    } else {
        V[i] = v;
    }
}

int* Vetor::getVetor() {
    return V;
}

int Vetor::operator[](int i) const {
    if ((i < 0) || (i >= n)) {
        cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
        exit(5);
    }
    return V[i];
}

int &Vetor::operator[](int i) {
    if ((i < 0) || (i >= n)) {
        cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
        exit(5);
    }
    return V[i];
}

void Vetor::escreve() {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << V[i];
        if (i < n - 1)
            cout << ", ";
    }
    cout << "]";
}

void Vetor::swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void Vetor::BubbleSort() {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
            if (V[j] < V[j - 1])
                swap(V[j], V[j - 1]);
}

void Vetor::InsertionSort() {
    for (int i = 0; i < n; i++) {
        int key = V[i];
        int j = i - 1;
        while (j >= 0 && V[j] > key) {
            V[j + 1] = V[j];
            j--;
        }
        V[j + 1] = key;
    }
}

void Vetor::SelectionSort() {
    for (int i = 0; i < (n - 1); i++) {
        // Encontra o menor elemento
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (V[j] < V[min])
                min = j;
        // troca a posição atual com o menor elemento do vetor
        int aux = V[min];
        V[min] = V[i];
        V[i] = aux;
    }
}

int Vetor::partition(int* __restrict__ A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i = i + 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void Vetor::QuickSort(int* __restrict__ A, int p, int r) {
    int q;
    if (r > p) {
        q = partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

void Vetor::Merge(int* __restrict__ A, int p, int q, int r) {
    int n1, n2;
    n1 = q - p + 1;
    n2 = r - q;
    int L[n1 + 1];
    int R[n2 + 1];
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[q + j + 1];
    }
    L[n1] = INT_MAX - 1;
    R[n2] = INT_MAX - 1;

    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++) {
        if ((L[i] <= R[j])) {
            A[k] = L[i];
            i = i + 1;
        } else {
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void Vetor::MergeSort(int* __restrict__ A, int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

