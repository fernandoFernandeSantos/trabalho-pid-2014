/* 
 * File:   Pixel.h
 * Author: root
 *
 * Created on 17 de Abril de 2014, 18:10
 */

#ifndef PIXEL_H
#define	PIXEL_H

#include <stdlib.h>
#include <iostream>
using namespace std;

class Pixel {
public:
    Pixel();
    Pixel(unsigned char r, unsigned char g, unsigned char b);
    Pixel(const Pixel& orig);
    virtual ~Pixel();
    unsigned char GetB() const;
    unsigned char GetG() const;
    unsigned char GetR() const;
    void SetB(unsigned char T);
    void SetR(unsigned char T);
    void SetG(unsigned char T);
    void setRGB(unsigned char r, unsigned char g, unsigned char b);
    //saida
    friend ostream &operator <<(ostream &output, const Pixel &B);


    // Operador de atribuicao
    Pixel &operator =(const Pixel &B);

    // Operador de soma
    Pixel operator +(const Pixel &B);

    // Operador de subtracao
    Pixel operator -(const Pixel &B);

    //Operador de ou
    Pixel operator |(const Pixel &B);

    //operador de &
    Pixel operator &(const Pixel &B);

    //operador de ~
    void operator ~();

    //operador de /
    Pixel operator /(const Pixel &B);

    //sobrecarga de /
    Pixel operator /(const unsigned int divisor);

private:
    unsigned char R; // representante da cor vermelha
    unsigned char G; // representante da cor verde
    unsigned char B; // representante da cor azul
};

#endif	/* PIXEL_H */

