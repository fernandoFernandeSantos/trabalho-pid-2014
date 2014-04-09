/* 
 * File:   BMP.cpp
 * Author: fernandofernandes
 * 
 * Created on 9 de Abril de 2014, 18:19
 */

#include "BMP.h"

BMP::BMP() {
}

BMP::BMP(const BMP& orig) {
}

BMP::~BMP() {
}

BitMapHeader BMP::GetCabecalhoBitMap() const {
    return cabecalhoBitMap;
}

void BMP::SetCabecalhoBitMap(BitMapHeader cabecalhoBitMap) {
    this->cabecalhoBitMap = cabecalhoBitMap;
}

Header BMP::GetCabecalhoImagen() const {
    return cabecalhoImagen;
}

void BMP::SetCabecalhoImagen(Header cabecalhoImagen) {
    this->cabecalhoImagen = cabecalhoImagen;
}

CollorPallet* BMP::GetPaletaCores() const {
    return paletaCores;
}

void BMP::SetPaletaCores(CollorPallet* paletaCores) {
    this->paletaCores = paletaCores;
}