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
    

private:
    unsigned char R; // representante da cor vermelha
    unsigned char G; // representante da cor verde
    unsigned char B; // representante da cor azul
};

#endif	/* PIXEL_H */

