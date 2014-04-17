/* 
 * File:   BMP.cpp
 * Author: fernandofernandes
 * 
 * Created on 9 de Abril de 2014, 18:19
 */

#include "BMP.h"
#include <cmath>
#include <stdlib.h>

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