#ifndef VETOR_H
#define VETOR_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Implementa��o da classe Vetor gen�rico como template

template <class T> class Vetor {
private:
    int n; // O n�mero de elementos do vetor;
    T *V; // A estrutura que armazena os elementos
    void swap(T &a, T &b); // M�todo auxiliar para troca
    void realloc(); // m�todo auxiliar para realocar o vetor V.
    
public:
    void realloc(int n); // m�todo auxiliar para realocar o vetor V.
    // Construtores e destruidores
    Vetor(); // Construtor default
    Vetor(int tam); // Construtor com tamanho definido
    Vetor(const Vetor<T> &A); // Construtor de c�pia
    ~Vetor(); // Destruidor

    // Outros m�todos
    void add(T valor); // Adiciona mais uma posi��o ao final do vetor e
    // lhe atribui "valor";
    T get(int i); // obtem o valor armazenado na posi��o i do vetor
    void set(int i, T v); // seta o valor v na posi��o i do vetor

    //operador sobrecarregados
    T operator[](int i) const; // sobrecarga do operador [] para leitura
    T &operator[](int i); // sobrecarga do operador [] para escrita

    template <class Ta>
    friend ostream &operator <<(ostream &output, const Vetor<Ta> &B);

    // Operador de atribuicao
    Vetor<T> &operator =(const Vetor<T> &B);

    void escreve(); // escreve o vetor
    int searchSeq(T elem); // Busca sequencial
    int searchBin(T elem); // Busca Binária

    T* getVetor();
    int getSize();

    // M�todos de ordena��o
    void BubbleSort(); // ordena��o pelo m�todo da bolha
    void ShakerSort(); // ordena��o pelo m�todo oscilante
    void InsertionSort(); // ordena��o pelo m�todo de inser��o
    void SelectionSort(); // ordena��o pelo m�todo de sele��o
    void ShellSort(); // ordena��o pelo m�todo Shell
    void merge(T *vec, int vecSize);
    void mergeSort(T *vec, int vecSize);
};


// Implementa��o dos m�todos da classe Vetor

template <class T> Vetor<T>::Vetor() {
    // construtor default
    //cout << "Construtor default construindo vetor...\n";
    this->n = 0;
    this->V = NULL;
    //cout << "Vetor construido.\n";
}

template <class T> Vetor<T>::Vetor(int tam) {
    //cout << "Construtor inicializ�vel construindo vetor...\n";
    if (tam < 0) {
        cerr << "Erro: o n�mero de elementos n�o pode ser negativo.\n";
        cerr << "Ajustando n�mero de elementos para zero.\n";
        this->n = 0;
        this->V = NULL;
    } else {
        this->n = tam;
        this->V = new T[n];
        if (this->V == NULL) {
            cerr << "Erro 1: N�o � poss�vel construir um vetor com tamanho\n ";
            cerr << this->n << ".";
            exit(1);
        } else {
            for (int i = 0; i < this->n; i++)
                this->V[i] = 0;
        }
    }
    //cout << "Vetor constru�do\n";
}

template <class T> Vetor<T>::Vetor(const Vetor <T> &A) {
    // cout << "Construtor de c�pia construindo Vetor...\n";
    this->n = A.n;
    this->V = new T[this->n];
    if (this->V == NULL) {
        cerr << "Erro 2: N�o � poss�vel criar a c�pia do vetor.";
        exit(2);
    }
    for (int i = 0; i < this->n; i++) {
        this->V[i] = A.V[i];
    }
    // cout << "Vetor constru�do.";
}

template <class T> Vetor<T>::~Vetor() {
    //cout << "Destruindo Vetor...\n";
    delete[] V;
    //cout << "Vetor destru�do\n";
}

template <class T> void Vetor<T>::realloc() {
    if (n == 0) // N�o h� elementos no vetor;
    {
        this->V = new T[++n];
        if (this->V == NULL) // Aloca��o falhou
        {
            cerr << "Erro 3: N�o � poss�vel redimensionar o vetor.";
            exit(3);
        }
    } else {
        int *aux = new T[n];
        if (aux == NULL) {
            cerr << "Erro 3: N�o � poss�vel redimensionar o vetor.";
            exit(3);
        }
        for (int i = 0; i < (n); i++)
            aux[i] = this->V[i];
        delete[] this->V;
        this->V = new T [++n];
        if (this->V == NULL) {
            cerr << "Erro 3: N�o � poss�vel redimensionar o vetor.";
            exit(3);
        }
        for (int i = 0; i < (n - 1); i++)
            this->V[i] = aux[i];
        this->V[n - 1] = 0;
        delete[] aux;
    }
    return;
}

template <class T> void Vetor<T>::realloc(int n) {
    if (n == 0) // N�o h� elementos no vetor;
    {
        this->V = new T[++n];
        if (this->V == NULL) // Aloca��o falhou
        {
            cerr << "Erro 3: N�o � poss�vel redimensionar o vetor.";
            exit(3);
        }
    } else {
        T *aux = new T[n];
        if (aux == NULL) {
            cerr << "Erro 3: N�o � poss�vel redimensionar o vetor.";
            exit(3);
        }
        for (int i = 0; i < (n); i++)
            aux[i] = this->V[i];
        delete[] this->V;
        this->V = new T [++n];
        if (this->V == NULL) {
            cerr << "Erro 3: N�o � poss�vel redimensionar o vetor.";
            exit(3);
        }
        for (int i = 0; i < (n - 1); i++)
            this->V[i] = aux[i];
        this->V[n - 1] = 0;
        delete[] aux;
    }
    return;
}

template <class T> void Vetor<T>::add(T valor) {
    realloc();
    this->V[n - 1] = valor;
    return;
}

template <class T> T Vetor<T>::get(int i) {
    if ((i < 0) || (i > n)) {
        cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
        return 0;
    } else {
        return V[i];
    }
}

template <class T> void Vetor<T>::set(int i, T v) {
    if ((i < 0) || (i > n)) {
        cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
        cerr << "Atribui��o abortada.\n";
        return;
    } else {
        V[i] = v;
    }
}

template <class T> T Vetor<T>::operator[](int i) const {
    if ((i < 0) || (i >= n)) {
        cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
        exit(5);
    }
    return V[i];
}

template <class T> T &Vetor<T>::operator[](int i) {
    if ((i < 0) || (i >= n)) {
        cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
        exit(5);
    }
    return V[i];
}

template <class T> void Vetor<T>::escreve() {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << V[i];
        if (i < n - 1)
            cout << ", ";
    }
    cout << "]";
}

template <class T> int Vetor<T>::searchSeq(T elem) {
    int i = 0;

    for (i = 0; (i < n); i++) {
        if (V[i] == elem) //  achou
            return i;
    }
    return -1; //não achou
}

template <class T> int Vetor<T>::searchBin(T elem) {
    int lo = 0;
    int hi = n - 1;
    int i = 0;
    while (lo <= hi) {
        i = (lo + hi) / 2;
        if (V[i] == elem)
            return i; // Achou
        if (elem < V[i])
            hi = i - 1; // Pesquisa na metade esquerda
        else
            lo = i + 1; // Pesquisa na metade direita
    }
    return -1;
}

template <class T> void Vetor <T>::swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

template <class T> void Vetor<T>::BubbleSort() {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
            if (V[j] < V[j - 1])
                swap(V[j], V[j - 1]);
}

template <class T> void Vetor <T>::ShakerSort() {
    bool troca;
    do {
        troca = false;
        for (int i = (n - 1); i > 0; i--) {
            if (V[i - 1] > V[i]) {
                swap(V[i - 1], V[i]);
                troca = true;
            }
        }
        for (int i = 1; i < n; i++) {
            if (V[i - 1] > V[i]) {
                swap(V[i - 1], V[i]);
                troca = true;
            }
        }
    } while (troca); // continua at� n�o haver mais trocas
}

template <class T> void Vetor <T>::InsertionSort() {
    for (int i = 1; i < n; i++) {
        T aux = this->V[i];
        int j = 0;
        for (j = i; (j > 0) && (aux < this->V[j - 1]); j--)
            this->V[j] = this->V[j - 1];
        this->V[j] = aux;
    }
}

template <class T> void Vetor <T>::SelectionSort() {
    for (int i = 0; i < (n - 1); i++) {
        // Encontra o menor elemento
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (V[j] < V[min])
                min = j;
        // troca a posi��o atual com o menor elemento do vetor
        T aux = V[min];
        V[min] = V[i];
        V[i] = aux;
    }
}

template <class T> void Vetor <T>::ShellSort() {
    const int MAXGAPS = 1; // N�mero de gaps
    const int FACTOR = 1; // Multiplicador para encontrar os gaps
    int gaps[MAXGAPS]; // vetor com os gaps

    // preeenche o vetor com os gaps adequados
    for (int i = 0; i < MAXGAPS; i++)
        gaps[MAXGAPS - (i + 1)] = (FACTOR * i) + 1;

    for (int k = 0; k < MAXGAPS; k++) {
        int gap = gaps[k];
        for (int i = gap; i < (this->n); i++) {
            T x = this->V[i];
            for (int j = (i - gap); (j >= 0) && (x < (this->V[j])); j -= gap) {
                this->V[j + gap] = this->V[j];
                this->V[j] = x;
            }
        }
    }
}

//===================================================================
//mergesort TEMPLATE

template <class T> void Vetor <T>::merge(T *vec, int vecSize) {
    int mid;
    int i, j, k;
    T *tmp = new T[vecSize];

    if (tmp == NULL) {
        exit(1);
    }

    mid = vecSize / 2;

    i = 0;
    j = mid;
    k = 0;
    while (i < mid && j < vecSize) {
        if (vec[i] <= vec[j]) {
            tmp[k] = vec[i++];
        } else {
            tmp[k] = vec[j++];
        }
        ++k;
    }

    if (i == mid) {
        while (j < vecSize) {
            tmp[k++] = vec[j++];
        }
    } else {
        while (i < mid) {
            tmp[k++] = vec[i++];

        }
    }

    for (i = 0; i < vecSize; ++i) {
        vec[i] = tmp[i];
    }

    delete [] tmp;
}

template <class T> void Vetor <T>::mergeSort(T *vec, int vecSize) {
    int mid;

    if (vecSize > 1) {
        mid = vecSize / 2;
        mergeSort(vec, mid);
        mergeSort(vec + mid, vecSize - mid);
        merge(vec, vecSize);
    }
}

template <class T> T* Vetor <T>::getVetor() {
    return this->V;
}

template <class T> int Vetor <T>::getSize() {
    return this->n;
}

// Operador <<

template <class Ta>
ostream &operator <<(ostream &output, const Vetor<Ta> &B) {
    for (unsigned int i = 0; i < B.n; i++) {
        output << "Vet[" << i << "]= " << B.V[i]
                << "\n";
    }
    return output;
}

template <class T>
Vetor<T> &Vetor<T>::operator =(const Vetor<T> &B) {
    // verifica a auto-atribuicao
    if (this != &B) {
        // Verifica se a matriz recebedora ja existe e limpa-a.
        if (this->V) {
            try {
                // o vetor existe. limpe-0
                for (unsigned int i = 0; i< this->n; i++) {
                    delete [] this->V;
                }
            } catch (std::exception &e) {
                cout << e.what();
            }
        }
        this->n = B.n;
        // aloca com o novo tamanho
        this->V = new T[this->n];

        //copia os valores para a matriz
        for (unsigned int i = 0; i < this->n; i++)
            this->V[i] = B.V[i];
    }
    return (*this);
}
#endif // VECTOR_H
