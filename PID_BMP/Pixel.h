/* 
 * File:   Pixel.h
 * Author: root
 *
 * Created on 17 de Abril de 2014, 18:10
 */

#ifndef PIXEL_H
#define	PIXEL_H

class Pixel {
public:
    Pixel();
    Pixel(const Pixel& orig);
    virtual ~Pixel();
    unsigned char GetB() const;
    unsigned char GetG() const;
    unsigned char GetT() const;
    unsigned char GetR() const;
    void SetT(unsigned char T);
    void SetB(unsigned char T);
    void SetR(unsigned char T);
    void SetG(unsigned char T);
    void setRGB(unsigned char r, unsigned char g, unsigned char b, 
                        unsigned char t);

private:
    unsigned char R; // representante da cor vermelha
    unsigned char G; // representante da cor verde
    unsigned char B; // representante da cor azul
    unsigned char T; // representante da transparência em BMPs com 32 bits

};

#endif	/* PIXEL_H */

