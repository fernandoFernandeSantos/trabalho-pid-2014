/* 
 * File:   Vetor.h
 * Author: alunos
 *
 * Created on 31 de Julho de 2014, 10:38
 */

#ifndef VETOR_H
#define	VETOR_H
#include <cstdlib>
#include "Vetor.h"
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

class Vetor {
private:
    u_int64_t quantTrocas; //quantidade de trocas
    u_int64_t quantComp; //quantidade de comparações
    int n; // O número de elementos do vetor;
    int *V; // A estrutura que armazena os elementos
    bool fromHere;

    int partition(int* A, int p, int r) {
        int x = A[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            this->quantComp++;
            if (A[j] <= x) {
                this->quantTrocas++;
                i = i + 1;
                swap(A[i], A[j]);
            }
        }
        this->quantTrocas++;
        swap(A[i + 1], A[r]);
        return i + 1;
    }

    void QuickSort(int* A, int p, int r) {
        int q;
        if (r > p) {
            q = partition(A, p, r);
            QuickSort(A, p, q - 1);
            QuickSort(A, q + 1, r);
        }
    }

    void Merge(int* A, int p, int q, int r) {
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
            this->quantComp++;
            if ((L[i] <= R[j])) {
                this->quantTrocas++;
                A[k] = L[i];
                i = i + 1;
            } else {
                A[k] = R[j];
                j = j + 1;
            }
        }
    }
public:

    Vetor() {
        // construtor default
        cout << "Construtor default construindo vetor...\n";
        n = 0;
        V = NULL;
        cout << "Vetor construido.\n";
        this->quantComp = 0;
        this->quantTrocas = 0;
        this->fromHere = false;
    }

    Vetor(int tam) {
        //cout << "Construtor inicializável construindo vetor...\n";
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
        this->quantComp = 0;
        this->quantTrocas = 0;
        this->fromHere = true;
        //cout << "Vetor construído\n";
    }

    Vetor(const Vetor &A) {
       // cout << "Construtor de cópia construindo Vetor...\n";
        this->n = A.n;
        V = new int[this->n];
        if (V == NULL) {
            cerr << "Erro 2: Não é possível criar a cópia do vetor.";
            exit(2);
        }
        for (int i = 0; i < this->n; i++) {
            this->V[i] = A.V[i];
        }
        //cout << "Vetor construído.";
        this->fromHere = false;
    }

    ~Vetor() {
        if (this->fromHere) {
            cout << "Destruindo Vetor...\n";
            delete[] V;
            cout << "Vetor destruído\n";
        }
    }

    void realloc() {
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

    void add(int valor) {
        realloc();
        V[n - 1] = valor;
        return;
    }

    int get(int i) {
        if ((i < 0) || (i > n)) {
            cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
            return 0;
        } else {
            return V[i];
        }
    }

    int getTamanho() {
        return this->n;
    }

    void set(int i, int v) {
        if ((i < 0) || (i > n)) {
            cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
            cerr << "Atribuição abortada.\n";
            return;
        } else {
            V[i] = v;
        }
    }

    int* getVetor() {
        return V;
    }

    int operator[](int i) const {
        if ((i < 0) || (i >= n)) {
            cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
            exit(5);
        }
        return V[i];
    }

    int &operator[](int i) {
        if ((i < 0) || (i >= n)) {
            cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
            exit(5);
        }
        return V[i];
    }

    void escreve() {
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << V[i];
            if (i < n - 1)
                cout << ", ";
        }
        cout << "]";
    }

    void BubbleSort() {
        for (int i = 0; i < n - 1; i++)
            for (int j = n - 1; j > i; j--) {
                this->quantComp++;
                if (V[j] < V[j - 1]) {
                    this->quantTrocas++;
                    swap(V[j], V[j - 1]);
                }
            }
    }

    void InsertionSort() {
        for (int i = 0; i < n; i++) {
            int key = V[i];
            int j = i - 1;
            this->quantComp++;
            while (j >= 0 && V[j] > key) {
                //this->quantComp++;
                //this->quantTrocas++;
                V[j + 1] = V[j];
                j--;
            }
            this->quantTrocas++;
            V[j + 1] = key;
        }
    }

    void SelectionSort() {
        for (int i = 0; i < (n - 1); i++) {
            // Encontra o menor elemento
            int min = i;
            for (int j = i + 1; j < n; j++) {
                this->quantComp++;
                if (V[j] < V[min]) {
                    min = j;
                }
            }
            // troca a posição atual com o menor elemento do vetor
            this->quantTrocas++;
            int aux = V[min];
            V[min] = V[i];
            V[i] = aux;
        }
    }

    void setVetor(int* vet, int n) {
        if (vet == NULL)
            return;
        this->n = n;
        this->V = vet;
        this->fromHere = false;
    }

    u_int64_t getQuantComp() const {
        return this->quantComp;
    }

    u_int64_t getQuantTrocas() const {
        return this->quantTrocas;
    }

    void fill(int valor) {
        for (int i = 0; i < this->n; i++) {
            this->V [i] = 0;

        }
    }

    void MergeSort(int* A, int p, int r) {
        int q;
        if (p < r) {
            q = (p + r) / 2;
            MergeSort(A, p, q);
            MergeSort(A, q + 1, r);
            Merge(A, p, q, r);
        }
    }

    void swap(int &a, int &b) {
        int c = a;
        a = b;
        b = c;
    }

    void MergeCall() {
        this->MergeSort(this->V, this->V[0], this->V[this->n - 1]);
    }

    void QuickCall() {
        this->QuickSort(this->V, this->V[0], this->V[this->n - 1]);
    }

    void zeraTEC() {
        this->quantTrocas = 0;
        this->quantComp = 0;
    }
};

#endif	/* VETOR_H */

