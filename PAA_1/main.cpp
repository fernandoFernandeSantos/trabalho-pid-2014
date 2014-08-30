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

void sort(CaseGenerator *seq, CaseGenerator *rand, CaseGenerator *inv) {
    Vetor resSeq, resRand, resInv;

    uint posSize;
    //randomico
    cout << "Caso Aleatorio\n";
    cout << "BubleSort Troca, Compar,SelectionSort Troca, Compar, InsertionSort Troca, Compar, "
            "MergeSort Troca, Compar, QuickSort Troca, Compar\n";
       
    for (int i = 0; i < 6; i++) {
        posSize = 0;
        while (posSize < 19) {
            //cout << "Vetor posicao " << posSize << " Tamanho " << rand[i].GetSizeAt(i) << ",";
            resRand.setVetor(rand[i].GetVetor(posSize), rand[i].GetSizeAt(posSize));
            cout << "Size " << i << " " << posSize << " " << resRand.getTamanho() << endl;
            Vetor buble(resRand), sele(resRand), inser(resRand), mer(resRand), quick(resRand);
            //ordena buble
            buble.BubbleSort();
            cout << buble.getQuantTrocas() << ", " << buble.getQuantComp() << ",";
            //ordena selection
            sele.SelectionSort();
            cout <<sele.getQuantTrocas() << ", " << sele.getQuantComp() << ",";
            //ordena selection
            inser.InsertionSort();
            cout << inser.getQuantTrocas() << ", " << inser.getQuantComp() << ",";
            //ordena selection
            mer.MergeCall();
            cout << mer.getQuantTrocas() << ", " << mer.getQuantComp() << ",";
             //ordena quick
            buble.QuickCall();
            cout << buble.getQuantTrocas() << ", " << buble.getQuantComp() << ", ";
            buble.zeraTEC();
            posSize++;
        }
        cout << "\n";
    }
    cout << "\nCaso Sequencial\n";
    cout << "BubleSort Troca, Compar,SelectionSort Troca, Compar, InsertionSort Troca, Compar, "
            "MergeSort Troca, Compar, QuickSort Troca, Compar\n";
    for (int i = 0; i < 2; i++) {
        posSize = 0;
        while (posSize < 19) {
            //cout << "Vetor posicao " << posSize << " Tamanho " << rand[i].GetSizeAt(i) << ",";
            resSeq.setVetor(seq[i].GetVetor(posSize), seq[i].GetSizeAt(posSize));
            cout << "Size " << i << " " << posSize << " " << resSeq.getTamanho() << endl;
            Vetor buble(resSeq), sele(resSeq), inser(resSeq), merge(resSeq), quick(resSeq);
            //ordena buble
            buble.BubbleSort();
            cout << buble.getQuantTrocas() << ", " << buble.getQuantComp() << ",";
            //ordena selection
            sele.SelectionSort();
            cout << sele.getQuantTrocas() << ", " << sele.getQuantComp() << ",";
            //ordena selection
            inser.InsertionSort();
            cout << inser.getQuantTrocas() << ", " << inser.getQuantComp() << ",";
            //ordena selection
            /*merge.MergeCall();
            cout << merge.getQuantTrocas() << ", " << merge.getQuantComp() << ",";
            //ordena quick
            quick.QuickCall();
            cout << quick.getQuantTrocas() << ", " << quick.getQuantComp() << ", ";
             */posSize++;
        }
        cout << "\n";

    }
    cout << "\nCaso Invertido\n";
    cout << "BubleSort Troca, Compar,SelectionSort Troca, Compar, InsertionSort Troca, Compar, "
            "MergeSort Troca, Compar, QuickSort Troca, Compar\n";
    for (int i = 0; i < 2; i++) {
        posSize = 0;
        while (posSize < 19) {
            //cout << "Vetor posicao " << posSize << " Tamanho " << rand[i].GetSizeAt(i) << ",";
            resInv.setVetor(inv[i].GetVetor(posSize), inv[i].GetSizeAt(posSize));
            cout << "Size " << i << " " << posSize << " " << resSeq.getTamanho() << endl;
            Vetor buble(resInv), sele(resInv), inser(resInv), merge(resInv), quick(resInv);
            //ordena buble
            buble.BubbleSort();
            cout << buble.getQuantTrocas() << ", " << buble.getQuantComp() << ",";
            //ordena selection
            sele.SelectionSort();
            cout << sele.getQuantTrocas() << ", " << sele.getQuantComp() << ",";
            //ordena selection
            inser.InsertionSort();
            cout << inser.getQuantTrocas() << ", " << inser.getQuantComp() << ",";
            //ordena selection
            merge.MergeCall();
            cout << merge.getQuantTrocas() << ", " << merge.getQuantComp() << ",";
            //ordena quick
            /*quick.QuickCall();
            cout << quick.getQuantTrocas() << ", " << quick.getQuantComp() << ", ";
             */posSize++;
        }
        cout << "\n";

    }
}

int main() {

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

    //executa ordenação
    sort(sequencial, randomicos, invertido);

    delete [] randomicos;
    delete [] sequencial;
    delete [] invertido;
    return 0;
}

