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
      uint lin; // armazena o numero de linhas
      uint col; // armazena o numero de colunas
      T **mat; // estrutura que armazena a matriz

   // Atributos e metodos publicos
   public:
      Matriz(uint l = 0, uint c = 0); // Construtor default inicializavel
      Matriz(const Matriz &A);	    // Construtor de copia
      ~Matriz();		    // destruidor
      void fill(T valor);	    // preenche a matriz com um valor 
      T get(uint i, uint j);	    // retorna o elemento mat[i][j]
      void set(uint i,unsigned  int j, T valor);// atribui valor ao elemento mat[i][j]
      uint getLinha();
      uint getColuna();
      void mAlloc(uint l, uint c);
      bool isEmpty();

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

template <class T>
void Matriz<T>::mAlloc(uint l, uint c)
{
   cout << "Executando construtor default inicializavel.\n";
   this->lin = l;
   this->col = c;
   if ((l == 0) || (c == 0))
   {
      // cria uma estrutura nula
      this->mat = NULL;
   }
   else
   {
      // cria a matriz com dimensoes validas
      mat = new T*[l];
      for (uint i = 0; i < l; i++)
	 mat[i] = new T[c];
   }
   return;
}

//-------------------------------------------------------------------------
template <class T>
Matriz<T>::Matriz(uint l, uint c)
{
   cout << "Executando construtor default inicializavel.\n";
   this->lin = l;
   this->col = c;
   if ((l == 0) || (c == 0))
   {
      // cria uma estrutura nula
      this->mat = NULL;
   }
   else
   {
      // cria a matriz com dimensoes validas
      mat = new T*[l];
      for (uint i = 0; i < l; i++)
	 mat[i] = new T[c];
   }
   return;
}
//-------------------------------------------------------------------------
// Construtor de copia
template<class T>
Matriz<T>::Matriz(const Matriz &A)
{
   cout << "Executando construtor de copia.\n";
   this->lin = A.lin;
   this->col = A.col;
   this->mat = new T*[this->lin];
   for (uint i = 0; i < this->lin; i++)
   {
      this->mat[i] = new T[this->col];
   }
   for (uint i = 0; i < this->lin; i++)
      for (uint j = 0; j < this->col; j++)
	 this->mat[i][j] = A.mat[i][j];
   return;
}

////-------------------------------------------------------------------------

// destruidor
template <class T>
Matriz<T>::~Matriz()
{
   cout << "Executando destruidor.\n";
   if (this->mat)
   {
      for (uint i = 0; i < this->lin; i++)
	 delete[] this->mat[i];
      delete[] this->mat;
   }
}

//-------------------------------------------------------------------------

template <class T>
bool Matriz<T>::isEmpty(){
    return (this->lin == 0 || this->col ==0);
}

//-------------------------------------------------------------------------

template <class T>
void Matriz<T>::fill(T valor)
{
   for (uint i = 0; i < this->lin; i++)
      for (uint j = 0; j < this->col; j++)
	 this->mat[i][j] = valor;
   return;
}
//--------------------------------------------------------------------------
template <class T>
uint Matriz<T>::getLinha(){
    return this->lin;
}

template <class T>
uint Matriz<T>::getColuna(){
    return this->col;
}

//-------------------------------------------------------------------------

template <class T>
T Matriz<T>::get(uint i, uint j)
{
   // testa erros de limite
   if (/*(i < 0) || (j < 0) || */ (i >= this->lin) || (j >= this->col))
   {
      cout << "Erro: Tentativa de acesso fora dos limites.\n";
      exit (0);
   }

   return this->mat[i][j];
}

//-------------------------------------------------------------------------

template <class T>
void Matriz<T>::set(uint i, uint j, T valor)
{
   // testa erros de limite
   if (/*(i < 0) || (j < 0) || */ (i >= this->lin) || (j >= this->col))
   {
      cout << "Erro: Tentativa de acesso fora dos limites.\n";
      exit (0);
   }

   this->mat[i][j] = valor;
   return;
}

//-------------------------------------------------------------------------

// Operador >> 
template <class Ta>
istream &operator >>(istream &input, Matriz<Ta> &B)
{
   for (int i = 0; i < B.lin; i++)
      for (int j = 0; j < B.col; j++)
      {
	 cout << "Mat[" << i << "][" << j << "]: ";
	 input >> B.mat[i][j];
      }
   return input;
}

//-------------------------------------------------------------------------

// Operador <<
template <class Ta>
ostream &operator <<(ostream &output, const Matriz<Ta> &B)
{
   for (uint i = 0; i < B.lin; i++)
   {
      for (uint j = 0; j < B.col; j++)
	 output << "Mat[" << i << "][" << j << "] = " << B.mat[i][j] 
	    << "\t";
      output << endl;
   }
   return output;
}

//-------------------------------------------------------------------------

// Operador de atribuicao
template <class T>
Matriz<T> &Matriz<T>::operator =(const Matriz<T> &B)
{
   // verifica a auto-atribuicao
   if (this != &B)
   {
      // Verifica se a matriz recebedora ja existe e limpa-a.
      if (this->mat)
      {
	 // a matriz existe. limpe-a
     for (uint i = 0; i< this->lin; i++)
	 {
	    delete this->mat[i];
	 }
	 delete this->mat;
      }
      this->lin = B.lin;
      this->col = B.col;
      // aloca com o novo tamanho
      this->mat = new T*[this->lin];
      for (uint i = 0; i< this->lin; i++)
	 this->mat[i] = new T[this->col];
      //copia os valores para a matriz
      for (uint i = 0; i < this->lin; i++)
     for (uint j = 0; j < this->col; j++)
	    this->mat[i][j] = B.mat[i][j];
   }
   return (*this);
}

//-------------------------------------------------------------------------

// Operador +
template <class T>
Matriz<T> Matriz<T>::operator +(const Matriz<T> &B)
{
   // Testa se as dimensoes das matrizes sao compativeis
   if ((this->lin != B.lin) || (this->col != B.col))
   {
      cout << "\nErro: Nao e possivel somar matrizes com dimensoes"
	   << " diferentes.\n";
      exit(0);
   }

   Matriz<T> soma(this->lin, this->col);
   for (int i = 0; i < this->lin; i++)
      for (int j = 0; j < this->col; j++)
	 soma.mat[i][j] = this->mat[i][j] + B.mat[i][j];
   return soma;
}

//-------------------------------------------------------------------------

// Operador -
template <class T>
Matriz<T> Matriz<T>::operator -(const Matriz<T> &B)
{
   // Testa se as dimensoes das matrizes sao compativeis
   if ((this->lin != B.lin) || (this->col != B.col))
   {
      cout << "\nErro: Nao e possivel subtrair matrizes com dimensoes"
	   << " diferentes.\n";
      exit(0);
   }
   
   Matriz<T> dif(this->lin, this->col);
   for (int i = 0; i < this->lin; i++)
      for (int j = 0; j < this->col; j++)
	 dif.mat[i][j] = this->mat[i][j] - B.mat[i][j];
   return dif;
}

//-------------------------------------------------------------------------

// Operador *
template <class T>
Matriz <T> Matriz<T>::operator *(const Matriz<T> &B)
{
   // Testa se as dimensoes das matrizes sao compativeis
   if (this->col != B.lin) 
   {
      cout << "Erro: Nao e possivel multiplicar as matrizes.\n"
	   << "O numero de linhas da primeira e diferente do numero de "
	   << "colunas da segunda.";
      exit(0);
   }
   Matriz<T> mult(this->lin, B.col);
   mult.fill(0);
   for (int i = 0; i < this->lin; i++)
      for (int j = 0; j < B.col; j++)
	 for (int k = 0; k < this->col; k++)
	    mult.mat[i][j] += this->mat[i][k] * B.mat[k][j];
   return mult;
}


//-------------------------------------------------------------------------
