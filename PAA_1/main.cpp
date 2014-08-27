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
#include "GeneratedCases.h"

using namespace std;

void Fscanf(std::string nome, int size, int * v) {

    std::ifstream ifs;
    ifs.open(nome.c_str());
    if (ifs.fail()) {
        cout << "Falha ao abrir o arquivo";
        exit(1);
    }


    if (v != NULL) {
        delete[] v;
    }
    v = new int[size];
    for (int i = 0; i < size; i++) {
        ifs >> v[i];
    }
    ifs.close();

}

static void geraRandomico(GeneratedCases *rand, string pasta) {
    uint i = 0;
    ostringstream inputstring;
    for (int j = 1; j <= 6; j++) {
        int limit = 10000;
        while (limit <= 100000) {
            inputstring << pasta + "/arq" << limit << "n" << j << ".txt";
            string s = inputstring.str();
            Fscanf(s, rand[j].GetM(), rand[j].getVet(i));
            limit += 5000;
            i++;
        } //fim while limit

    } //fim for randomico
}

int main(int argc, char** argv) {

    FileGenerator novos;
    string t = "randomico";
    //pegando primeiro os randomicos
    GeneratedCases *randomicos = new GeneratedCases[6]();
    GeneratedCases *sequencial = new GeneratedCases[2]();
    GeneratedCases *invertido = new GeneratedCases[2]();
    for (u_char i = 0; i < 6; i++) {
        randomicos[i].initData(19, t);
    }
    for (u_char i = 0; i < 2; i++) {
        sequencial [i].initData(19, "sequencial");
        invertido [i].initData(19, "invertido");
    }
    //gera os arquivos
    cout << "É a primeira vez que rodas este algoritmo[S/n]? ";
    char a;
    cin >> a;
    if (a == 'S' || a == 's') {
        novos.generate("testes");
    }
    geraRandomico(randomicos, "testes");
    return 0;
}

