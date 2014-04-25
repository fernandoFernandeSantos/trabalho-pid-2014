/* 
 * File:   Pixel.cpp
 * Author: root
 * 
 * Created on 17 de Abril de 2014, 18:10
 */

#include "Pixel.h"

Pixel::Pixel() {
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b){
    this->R = r;
    this->B = b;
    this->G = g;
}

Pixel::Pixel(const Pixel& orig) {
    this->R = orig.R;
    this->G = orig.G;
    this->B = orig.B;
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

void Pixel::setRGB(unsigned char r, unsigned char g, unsigned char b){
    this->R = r;
    this->B = b;
    this->G = g;
}
