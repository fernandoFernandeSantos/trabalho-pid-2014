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
#include <exception>

BMP::BMP() {
}

BMP::BMP(const BMP& orig) {
}

BMP::~BMP() {
    //deletar paleta de cores
    if ((this->cabecalhoBitMap.GetBiCrlUsed() <= 256) && (this->cabecalhoBitMap.GetBiCrlUsed())) {
        delete this->paletaCores;
        this->paletaCores = NULL;
    }
    //deletar a matriz de pixels

    for (int i = 0; i < this->cabecalhoBitMap.GetBiWidth(); i++) {
        delete this->matrizPixels[i];
        this->matrizPixels[i] = NULL;
    }
    delete this->matrizPixels;
    this->matrizPixels = NULL;

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

void BMP::read(std::ifstream* input) {
    this->cabecalhoImagem.read(input);
    this->cabecalhoBitMap.read(input);
    //verifica se tem mapa de cores

    if (this->cabecalhoBitMap.GetBiCrlUsed() <= 256 && this->cabecalhoBitMap.GetBiCrlUsed()) { //tem mapa de cores
        this->paletaCores = new CollorPallet[(int) this->cabecalhoBitMap.GetBiCrlUsed()];
        //lê a paleta de cores
        unsigned char r, g, b, t;
        for (int i = 0; i < (4 * this->cabecalhoBitMap.GetBiCrlUsed()); i++) {
            input->read((char*) & t, sizeof (unsigned char));
            input->read((char*) & b, sizeof (unsigned char));
            input->read((char*) & g, sizeof (unsigned char));
            input->read((char*) & r, sizeof (unsigned char));
            this->paletaCores->setCor(r, g, b, t);
        }
    }
    //leitura dos dados (fazer aqui)
    if (this->cabecalhoBitMap.GetBiBitCount() == 1) {
    } //1bit
    if (this->cabecalhoBitMap.GetBiBitCount() == 4) {
    } //4 bits
    if (this->cabecalhoBitMap.GetBiBitCount() == 8) {
    } //8 bits

    if (this->cabecalhoBitMap.GetBiBitCount() == 24) { //24 bits
        //aloca matriz de pixels
        this->matrizPixels = new Pixel*[this->cabecalhoBitMap.GetBiWidth()];
        for (int i = 0; i < this->cabecalhoBitMap.GetBiWidth(); i++) {
            this->matrizPixels[i] = new Pixel[this->cabecalhoBitMap.GetBiHeigth()];
        }
        unsigned char r, g, b;
        int linha = 0, coluna = 0;
        while (!input->eof()) {
            input->read((char*) & b, sizeof (unsigned char));
            input->read((char*) & g, sizeof (unsigned char));
            input->read((char*) & r, sizeof (unsigned char));
            this->matrizPixels[linha][coluna].setRGB(r, g, b);
            coluna++;
            if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                linha++;
                coluna = 0;
            }

        }
    }
    if (this->cabecalhoBitMap.GetBiBitCount() == 32) { //32 bits
        //aloca matriz de pixels
        this->matrizPixels = new Pixel*[this->cabecalhoBitMap.GetBiWidth()];
        for (int i = 0; i < this->cabecalhoBitMap.GetBiWidth(); i++) {
            this->matrizPixels[i] = new Pixel[this->cabecalhoBitMap.GetBiHeigth()];
        }
        unsigned char r, g, b, t;
        int linha = 0, coluna = 0;
        while (!input->eof()) {
            input->read((char*) & t, sizeof (unsigned char));
            input->read((char*) & b, sizeof (unsigned char));
            input->read((char*) & g, sizeof (unsigned char));
            input->read((char*) & r, sizeof (unsigned char));
            this->matrizPixels[linha][coluna].setRGB(r, g, b, t);
            coluna++;
            if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                linha++;
                coluna = 0;
            }

        }
    }
}

void BMP::printInfo() {
    this->cabecalhoImagem.print();
    this->cabecalhoBitMap.print();
    int numeroCores = this->cabecalhoBitMap.GetBiCrlUsed();
    if (numeroCores == 16 || numeroCores == 256)
        for (int i = 0; i < numeroCores; i++) {
            std::cout << this->paletaCores[i].GetBlue() << " " << this->paletaCores[i].GetRed() << " "
                    << this->paletaCores[i].GetGreen() << "\n";
        }
}



