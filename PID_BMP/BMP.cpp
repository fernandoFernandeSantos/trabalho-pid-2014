/* 
 * File:   BMP.cpp
 * Author: fernandofernandes
 * 
 * Created on 9 de Abril de 2014, 18:19
 */

#include "BMP.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <fstream>

BMP::BMP() {
}

BMP::BMP(const BMP& orig) {
}

BMP::~BMP() {
    double numeroCores = pow(2, this->cabecalhoBitMap.GetBiBitCount());
    for (int i = 0; i < numeroCores; i++) {
        this->paletaCores[i].~CollorPallet();
    }
    free(this->paletaCores);
    this->cabecalhoImagem.~Header();
    this->cabecalhoBitMap.~BitMapHeader();

}

BitMapHeader BMP::GetCabecalhoBitMap() const {
    return cabecalhoBitMap;
}

void BMP::SetCabecalhoBitMap(BitMapHeader cabecalhoBitMap) {
    this->cabecalhoBitMap = cabecalhoBitMap;
}

Header BMP::GetCabecalhoImagem() const {
    return cabecalhoImagem;
}

void BMP::SetCabecalhoImagen(Header cabecalhoImagem) {
    this->cabecalhoImagem = cabecalhoImagem;
}

CollorPallet* BMP::GetPaletaCores() const {
    return paletaCores;
}

void BMP::SetPaletaCores(CollorPallet* paletaCores) {
    this->paletaCores = paletaCores;
}

Pixel** BMP::GetMatrizPixels() const {
    return matrizPixels;
}

void BMP::SetMatrizPixels(Pixel** matrizPixels) {
    this->matrizPixels = matrizPixels;
}

void BMP::read(char * nomeArquivo, std::ifstream* input) {
    input->open(nomeArquivo);
    this->cabecalhoImagem.read(input);
    this->cabecalhoBitMap.read(input);
    //verifica se tem mapa de cores 
    double numeroCores = pow(2, this->cabecalhoBitMap.GetBiBitCount());

    if ((numeroCores == 16) || (numeroCores == 256)) { //tem mapa de cores
        this->paletaCores = new CollorPallet[(int) numeroCores];
        //lê a paleta de cores
        unsigned char r, g, b, t;
        for (int i = 0; i < (4 * numeroCores); i++) {
            input->read((char*) & t, sizeof (unsigned char));
            input->read((char*) & b, sizeof (unsigned char));
            input->read((char*) & g, sizeof (unsigned char));
            input->read((char*) & r, sizeof (unsigned char));
            this->paletaCores->setCor(r, g, b, t);
        }
    }
}

void BMP::printInfo() {
    this->cabecalhoImagem.print();
    this->cabecalhoBitMap.print();
    double numeroCores = pow(2, this->cabecalhoBitMap.GetBiBitCount());
    if (numeroCores == 16 || numeroCores == 256)
        for (int i = 0; i < numeroCores; i++) {
            std::cout << this->paletaCores[i].GetBlue() << " " << this->paletaCores[i].GetRed() << " "
                    << this->paletaCores[i].GetGreen() << "\n";
        }
}



