/* 
 * File:   Ponto.cpp
 * Author: familia
 * 
 * Created on 15 de Novembro de 2014, 14:39
 */

#include "Ponto.h"

Ponto::Ponto() {
}

Ponto::Ponto(const Ponto& orig) {
    this->x = orig.x;
    this->y = orig.y;
}
Ponto::Ponto(unsigned int x, unsigned int y){
    this->x = x;
    this->y = y;
}

Ponto::~Ponto() {
}

unsigned int Ponto::GetX() const {
    return x;
}

void Ponto::SetX(unsigned int x) {
    this->x = x;
}

unsigned int Ponto::GetY() const {
    return y;
}

void Ponto::SetY(unsigned int y) {
    this->y = y;
}