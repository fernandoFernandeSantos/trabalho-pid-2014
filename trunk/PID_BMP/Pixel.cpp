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

// Operador de atribuicao
Pixel &Pixel::operator =(const Pixel &B)
{
    // verifica a auto-atribuicao
    if (this != &B)
    {
        this->R = B.GetR();
        this->G = B.GetG();
        this->B = B.GetB();
    }
    return (*this);
}

//-------------------------------------------------------------------------

// Operador +
Pixel Pixel::operator +(const Pixel &B)
{
    unsigned char a = this->GetR() + B.GetR();
    unsigned char b =  this->GetG() + B.GetG();
    unsigned char c = this->GetB() + B.GetB();
    Pixel soma(a, b, c);
    return soma;
}

//-------------------------------------------------------------------------

// Operador -
Pixel Pixel::operator -(const Pixel &B)
{
    unsigned char a = this->GetR() - B.GetR();
    unsigned char b =  this->GetG() - B.GetG();
    unsigned char c = this->GetB() - B.GetB();
    Pixel dif(a, b, c);
    return dif;
}
//-------------------------------------------------------------------------

//Operador |
Pixel Pixel::operator |(const Pixel &B){
    unsigned char a = this->GetR() | B.GetR();
    unsigned char b =  this->GetG() | B.GetG();
    unsigned char c = this->GetB() | B.GetB();
    Pixel ors(a, b, c);
    return ors;
}

//-------------------------------------------------------------------------
//operador &
Pixel Pixel::operator &(const Pixel &B){
    unsigned char a = this->GetR() & B.GetR();
    unsigned char b =  this->GetG() & B.GetG();
    unsigned char c = this->GetB() & B.GetB();
    Pixel ands(a, b, c);
    return ands;
}

void Pixel::operator ~(){
    unsigned char a = ~this->GetR();
    unsigned char b =  ~this->GetG();
    unsigned char c = ~this->GetB();
    this->setRGB(a, b, c);
}

Pixel Pixel::operator /(const Pixel &B){
    unsigned char a = this->GetR() / B.GetR();
    unsigned char b = this->GetG() / B.GetG();
    unsigned char c = this->GetB() / B.GetB();
    Pixel div(a,b,c);
    return div;
}

Pixel Pixel::operator /(const unsigned int divisor){
    unsigned char a = this->GetR();
    unsigned char b = this->GetG();
    unsigned char c = this->GetB();
    unsigned int temp = a + b + c;
    temp /=divisor;
    a = temp;
    Pixel div(a,a,a);
    return div;
}

//-------------------------------------------------------------------------
// Operador <<
ostream &operator <<(ostream &output, const Pixel &B)
{
    output << "[" << B.GetR() << "]" << "[" << B.GetG() << "]" <<
              "[" << B.GetB() << "]";
    return output;
}
