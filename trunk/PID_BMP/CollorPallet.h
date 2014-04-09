/* 
 * File:   CollorPallet.h
 * Author: marcelo
 *
 * Created on 9 de Abril de 2014, 14:34
 */

#ifndef COLLORPALLET_H
#define	COLLORPALLET_H

class CollorPallet {
private:
    
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reservado;//Campo reservado, deve ser 0

public:
    CollorPallet();
    CollorPallet(const CollorPallet& orig);
    virtual ~CollorPallet();

    unsigned char GetBlue() const;
    unsigned char GetGreen() const;
    unsigned char GetRed() const;
    unsigned char GetReservado() const;
    void SetBlue(unsigned char Blue);
    void SetGreen(unsigned char Green) ;
    void SetRed(unsigned char Red);
    void SetReservado(unsigned char Reservado);

};

#endif	/* COLLORPALLET_H */

