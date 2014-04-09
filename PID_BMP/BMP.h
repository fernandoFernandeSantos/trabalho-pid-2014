/* 
 * File:   BMP.h
 * Author: fernandofernandes
 *
 * Created on 9 de Abril de 2014, 18:19
 */

#ifndef BMP_H
#define	BMP_H

#include "CollorPallet.h"
#include "BitMapHeader.h"
#include "Header.h"

class BMP {
public:
    BMP();
    BMP(const BMP& orig);
    virtual ~BMP();
    BitMapHeader GetCabecalhoBitMap() const;
    SetCabecalhoBitMap(BitMapHeader cabecalhoBitMap);
    GetCabecalhoImagen() const;
    void SetCabecalhoImagen(Header cabecalhoImagen);
    CollorPallet* GetPaletaCores() const;
    void BMP::SetPaletaCores(CollorPallet* paletaCores);

private:
    CollorPallet *paletaCores;
    BitMapHeader cabecalhoBitMap;
    Header cabecalhoImagen;
};



#endif	/* BMP_H */

