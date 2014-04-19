/* 
 * File:   BMP.h
 * Author: fernandofernandes
 *
 * Created on 9 de Abril de 2014, 18:19
 */

#ifndef BMP_H

#include "CollorPallet.h"
#include "BitMapHeader.h"
#include "Header.h"
#include "Pixel.h"
#define	BMP_H


class BMP {
public:
    BMP();
    BMP(const BMP& orig);
    virtual ~BMP();
    BitMapHeader GetCabecalhoBitMap() const;
    void SetCabecalhoBitMap(BitMapHeader cabecalhoBitMap);
    Header GetCabecalhoImagem() const;
    void SetCabecalhoImagen(Header cabecalhoImagen);
    CollorPallet* GetPaletaCores() const;
    void SetPaletaCores(CollorPallet* paletaCores);
    Pixel **GetMatrizPixels() const;
    void SetMatrizPixels(Pixel** matrizPixels);
    void read(std::ifstream *input);
    void printInfo();
    double* valorMedio();
    bool salvar(const char* nomeArquivo);
    int findIndex(unsigned char r, unsigned char g, unsigned char b);

private:
    CollorPallet *paletaCores; //paleta de cores ou mapa de cores
    BitMapHeader cabecalhoBitMap; //cabeçalho do mapa de bits
    Header cabecalhoImagem; //cabeçalho do arquivo
    Pixel **matrizPixels; //armazena os dados do bmp


};



#endif	/* BMP_H */

