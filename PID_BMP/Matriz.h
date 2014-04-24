// Arquivo: Matriz.h
// Implementa: Uma classe Matriz generica dinamica
// Autor: Prof. Josue Pereira de Castro
// Data: 09-07-2007

#include <stdlib.h>
#include <iostream>
using namespace std;

template <class T>
class Matriz
{
   // Atributos e metodos privados 
   private:
      int lin; // armazena o numero de linhas
      int col; // armazena o numero de colunas
      T **mat; // estrutura que armazena a matriz

   // Atributos e metodos publicos
   public:
      Matriz(int l = 0, int c = 0); // Construtor default inicializavel
      Matriz(const Matriz &A);	    // Construtor de copia
      ~Matriz();		    // destruidor
      void fill(T valor);	    // preenche a matriz com um valor 
      T get(int i, int j);	    // retorna o elemento mat[i][j]
      void set(int i, int j, T valor);// atribui valor ao elemento mat[i][j]

      // Operadores sobrecarregados

      // Operador >>
      template <class Ta>
      friend istream &operator >>(istream &input, Matriz<Ta> &B);

      // Operador <<
      template <class Ta>
      friend ostream &operator <<(ostream &output, const Matriz<Ta> &B);

      // Operador de atribuicao
      Matriz<T> &operator =(const Matriz<T> &B);

      // Operador de soma
      Matriz<T> operator +(const Matriz<T> &B);

      // Operador de subtracao
      Matriz<T> operator -(const Matriz<T> &B);

      // Operador de multiplicacao
      Matriz<T> operator *(const Matriz<T> &B);

};

