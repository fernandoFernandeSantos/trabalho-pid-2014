/* 
 * File:   Vetor.h
 * Author: alunos
 *
 * Created on 31 de Julho de 2014, 10:38
 */

#ifndef VETOR_H
#define	VETOR_H

class Vetor {
private:
    int n; // O número de elementos do vetor;
    int *V; // A estrutura que armazena os elementos
    void swap(int &a, int &b); // Método auxiliar para troca
    void realloc(); // método auxiliar para realocar o vetor V.
    //metodos privados
    int partition(int* __restrict__  vec, int esquerdo, int direito);
    void Merge(int* __restrict__ A, int p, int q, int r);
public:
    // Construtores e destruidores
    Vetor(); // Construtor default
    Vetor(int tam); // Construtor com tamanho definido
    Vetor(const Vetor &A); // Construtor de cópia
    ~Vetor(); // Destruidor

    // Outros métodos
    void add(int valor); // Adiciona mais uma posição ao final do vetor e 
    // lhe atribui "valor";
    int get(int i); // obtem o valor armazenado na posição i do vetor
    void set(int i, int v); // seta o valor v na posição i do vetor
    int operator[](int i) const; // sobrecarga do operador [] para leitura
    int &operator[](int i); // sobrecarga do operador [] para escrita
    void escreve(); // escreve o vetor
    int* getVetor();
    int getTamanho();
    // Métodos de ordenação 
    /*
     * Bubble Sort;
              Selection Sort;
              Insertion Sort;
              Quicksort;
              Mergesort
     * */
    void BubbleSort(); // ordenação pelo método da bolha
    void InsertionSort(); // ordenação pelo método de inserção
    void SelectionSort(); // ordenação pelo método de seleção
    
    //pagina 24 cormen
    void MergeSort(int* __restrict__ A, int p, int r);
    
    void QuickSort(int* __restrict__ A, int p, int r);
    


};

#endif	/* VETOR_H */

