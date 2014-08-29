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

int main(int argc, char** argv) {

    FileGenerator novos;
    //pegando primeiro os randomicos
    CaseGenerator *randomicos = new CaseGenerator[6]();
    CaseGenerator *sequencial = new CaseGenerator[2]();
    CaseGenerator *invertido = new CaseGenerator[2]();
    
    
    for (u_char i = 0; i < 6; i++) {
        randomicos[i].SetN(20);
        randomicos[i].Malloc("randomico");
    }
    for (u_char i = 0; i < 2; i++) {
        sequencial[i].SetN(20);
        invertido[i].SetN(20);
        sequencial [i].Malloc("sequencial");
        invertido [i].Malloc("invertido");
    }
    //gera os arquivos
    cout << "É a primeira vez que rodas este algoritmo[S/n]? ";
    char a;
    cin >> a;
    if (a == 'S' || a == 's') {
        novos.generate(pasta);
    }
    CaseGenerator::geraRandomico(randomicos, pastaProjeto + pasta);
    CaseGenerator::geraSequencial(sequencial, pastaProjeto + pasta);
    CaseGenerator::geraInvertido(invertido, pastaProjeto + pasta);

    //testes
    Vetor se;
    se.setVetor(sequencial[0].GetVetor(0), sequencial[0].GetSizeAt(0));
    se.SelectionSort();
    cout << "Comparações " << se.getQuantComp() << endl;
    cout << "Trocas " << se.getQuantTrocas() << endl;
    delete [] randomicos;
    delete [] sequencial;
    delete [] invertido;
    return 0;
}

