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
#include "Matriz.h"
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
    Matriz<Pixel> GetMatrizPixels() const;
    Matriz<int> GetHistogram() const;
    void SetMatrizPixels(Matriz<Pixel> matrizPixels);
    void read(std::ifstream *input);
    bool salvar(const char* nomeArquivo);
    u_char findIndex(unsigned char r, unsigned char g, unsigned char b);
    //aloca o histograma de acordo com a imagem
    void mallocHistogram();
    
    //operações
    long double * variancia(long double * valorMedio);
    long double * covariancia(BMP g2);
    long double* valorMedio();
    void printCabecalhoArquivo();
    void printCabecalhoImagem();
    bool makeHistogram();




private:
    CollorPallet *paletaCores; //paleta de cores ou mapa de cores
    BitMapHeader cabecalhoBitMap; //cabeçalho do mapa de bits
    Header cabecalhoImagem; //cabeçalho do arquivo
    //armazena os dados do bmp
    Matriz<Pixel> matrizPixels;
    Matriz<int> Histograma;


};



#endif	/* BMP_H */

