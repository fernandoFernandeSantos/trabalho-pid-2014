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
#include "CaseGenerator.h"

using namespace std;
string pastaProjeto = "/home/fernandofernandes/NetBeansProjects/PAA_1/";
string pasta = "testes";

void geraRandomico(CaseGenerator *rand, string pasta) {
    uint i = 0;
    std::ostringstream inputstring;
    string s = "";
    for (int j = 0; j < 6; j++) {
        int limit = 10000;
        while (limit <= 100000) {
            inputstring << pasta + "/arq" << limit << "n" << (j + 1) << ".txt";
            s = inputstring.str();
            rand[j].SetM(limit, j);
            rand[j].Fscanf(s, i, );
            limit += 5000;
            i++;
            inputstring.str("");
            s.clear();
        } //fim while limit

    } //fim for randomico
}

void geraSequencial(CaseGenerator* seq, string pasta) {
    std::ostringstream inputstring;
    string s = "";
    uint j = 0;
    for (int i = 0; i < 2; i++) {
        int limit = 10000;
        while (limit <= 100000) {
            inputstring << pasta + "/arq" << limit << "seq" << "n" << (i + 1) << ".txt";
            s = inputstring.str();
            seq[i].SetM(limit);
            seq[i].Fscanf(s, j++);
            inputstring.str("");
            inputstring.clear();
            limit += 5000;
            s.clear();
        }
    }
}

void geraInvertido(CaseGenerator* inv, string pasta) {
    std::ostringstream inputstring;
    string s = "";
    uint j = 0;
    for (int i = 0; i < 2; i++) {
        int limit = 10000;
        while (limit <= 100000) {
            inputstring << pasta + "/arq" << limit << "inv" << "n" << (i + 1) << ".txt";
            s = inputstring.str();
            inv[i].SetM(limit, j);
            inv[i].Fscanf(s, j);
            j++;
            inputstring.str("");
            inputstring.clear();
            limit += 5000;
            s.clear();
        }
    }
}

int main(int argc, char** argv) {

    FileGenerator novos;
    string t = "randomico";
    //pegando primeiro os randomicos
    CaseGenerator *randomicos = new CaseGenerator[6]();
    CaseGenerator *sequencial = new CaseGenerator[2]();
    CaseGenerator *invertido = new CaseGenerator[2]();
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
        novos.generate(pasta);
    }
    geraRandomico(randomicos, pastaProjeto + pasta);
    geraSequencial(sequencial, pastaProjeto + pasta);
    geraInvertido(invertido, pastaProjeto + pasta);

    //testes
    Vetor se;
    cout << "Comparações Antes" << se.getQuantComp() << endl;
    cout << "Trocas Antes" << se.getQuantTrocas() << endl;
    se.setVetor(sequencial[0].getVet(1), sequencial[0].GetM());

    se.InsertionSort();
    cout << "Comparações " << se.getQuantComp() << endl;
    cout << "Trocas " << se.getQuantTrocas() << endl;

    return 0;
}

