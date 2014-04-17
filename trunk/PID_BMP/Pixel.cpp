/* 
 * File:   Pixel.cpp
 * Author: root
 * 
 * Created on 17 de Abril de 2014, 18:10
 */

#include "Pixel.h"

Pixel::Pixel() {
}

Pixel::Pixel(const Pixel& orig) {
}

Pixel::~Pixel() {
}

unsigned char Pixel::GetB() const {
    return B;
}

void Pixel::SetB(unsigned char B) {
    this->B = B;
}

unsigned char Pixel::GetG() const {
    return G;
}

void Pixel::SetG(unsigned char G) {
    this->G = G;
}

unsigned char Pixel::GetR() const {
    return R;
}

void Pixel::SetR(unsigned char R) {
    this->R = R;
}

unsigned char Pixel::GetT() const {
    return T;
}

void Pixel::SetT(unsigned char T) {
    this->T = T;
}

void Pixel::setRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char t){
    this->T = t;
    this->R = r;
    this->B = b;
    this->G = g;
}
