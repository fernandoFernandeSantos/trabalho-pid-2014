/* 
 * File:   Ponto.h
 * Author: familia
 *
 * Created on 15 de Novembro de 2014, 14:39
 */

#ifndef PONTO_H
#define	PONTO_H

class Ponto {
public:
    Ponto();
    Ponto(unsigned int x, unsigned int y);
    Ponto(const Ponto& orig);

    unsigned int GetX() const;

    void SetX(unsigned int x);

    unsigned int GetY() const;

    void SetY(unsigned int y);

    virtual ~Ponto();
private:
    unsigned int x;
    unsigned int y;

};

#endif	/* PONTO_H */

