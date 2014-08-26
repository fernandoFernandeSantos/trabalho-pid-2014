#include "reader.h"
#include <iostream>
#include <new>
#include <cstdlib>

using namespace std;
reader::reader()
{
}

void reader::read(std::string nome, int size){

    std::ifstream ifs;
    ifs.open(nome.c_str());
    if(ifs.fail()){
        cout << "Falha ao abrir o arquivo";
        exit(1);
    }


    if(reader::v != NULL){
        delete[] reader::v;
    }

    reader::size = size;
    reader::v = new int[size];
    for(int i = 0; i < size; i++){
        ifs >> v[i];
    }
    ifs.close();

}


int *reader::getVector(){

    int *newv = new (nothrow) int[reader::size];
    if(newv == NULL){
        cout << "shit happend here" << endl;
    }
    for(int i = 0; i < reader::size; i++){
        newv[i] = reader::v[i];
    }

    return newv;

}


reader::~reader(){
    if(reader::v != NULL)
        delete[] reader::v;
}

int reader::size = 0;
int* reader::v;
