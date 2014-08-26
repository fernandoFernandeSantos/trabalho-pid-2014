/* 
 * File:   CollorPallet.cpp
 * Author: marcelo
 * 
 * Created on 9 de Abril de 2014, 14:34
 */

#include "CollorPallet.h"

CollorPallet::CollorPallet() {
}

CollorPallet::CollorPallet(const CollorPallet& orig) {
    this->Blue = orig.GetBlue();
    this->Green = orig.GetGreen();
    this->Red = orig.GetRed();
    this->Reservado = orig.GetReservado();
}

 CollorPallet::CollorPallet(unsigned char r, unsigned char g, unsigned char b, unsigned char res){
    this->Blue = b;
    this->Green = g;
    this->Red = r;
    this->Reservado = res;
 }
 
CollorPallet::~CollorPallet() {
}

unsigned char CollorPallet::GetBlue() const {
    return Blue;
}

void CollorPallet::SetBlue(unsigned char Blue) {
    this->Blue = Blue;
}

unsigned char CollorPallet::GetGreen() const {
    return Green;
}

void CollorPallet::SetGreen(unsigned char Green) {
    this->Green = Green;
}

unsigned char CollorPallet::GetRed() const {
    return Red;
}

void CollorPallet::SetRed(unsigned char Red) {
    this->Red = Red;
}

unsigned char CollorPallet::GetReservado() const {
    return Reservado;
}

void CollorPallet::SetReservado(unsigned char Reservado) {
    this->Reservado = Reservado;
}

void CollorPallet::setCor(unsigned char r, unsigned char g,
        unsigned char b, unsigned char reservado){
    this->Reservado = reservado;
    this->Red = r;
    this->Blue = b;
    this->Green = g;
}

CollorPallet &CollorPallet::operator =(const CollorPallet &orig){
    if(this != &orig){
        this->Blue = orig.Blue;
        this->Red = orig.Red;
        this->Green = orig.Green;
        this->Reservado = orig.Reservado;
    }
    return (*this);
}
