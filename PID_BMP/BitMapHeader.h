/* 
 * File:   BitMapHeader.h
 * Author: marcelo-note
 *
 * Created on 8 de Abril de 2014, 14:45
 */

#ifndef BITMAPHEADER_H
#define	BITMAPHEADER_H

#include <fstream>
#include <iostream>



class BitMapHeader {
private:
    unsigned int BiSize; //Tamanho do BitMadHeader
    unsigned int BiWidth; //Largura em pixels
    unsigned int BiHeigth; //Altura em pixels
    unsigned short BiPlanes; //Nudero de planos, sempre 1
    unsigned short BiBitCount; //Bits por pixel-indica, indiretamente, ainda  o número máximo de cores, que é 2
    unsigned int BiCompress; /*Compressão  usada. Pode ser:
                                                0 = BI_RGB _ sem compressão
                                                1 = BI_RLE8 – compressão RLE 8 bits
                                                2 = BI_RLE4 – compressão RLE 4 bits*/
    unsigned int BiSizeImage; /*Tamanho da imagem (dados) em byte
                                -  Se arquivo sem compressão, este campo pode ser ZERO.
                                -  Se imagem em true color, será Tamanho do arquivo (Bfsize)
                                menos deslocamento (BfOffSetBits)*/
    unsigned int BiXPPMeter; //Resolução horizontal, pixel por metro
    unsigned int BiYPPMeter; //Resolução vertical, pixel por metro
    unsigned int BiCrlUsed; /*Número de cores usadas na imagem. 
                            * Quando ZERO indica o uso do máximo de cores possível 
                            * pela quantidade de  Bits por pixel, que é 2*/
    unsigned int BiClrImport; /*Número de cores importantes(realmente usadas) na imagem.
                                Por exemplo das 256 cores, apenas 200 são efetivamente usadas.
                                Se todas são importantes pode ser ZERO. É útil quando for
                                exibir uma imagem em 1 dispositivo que suporte menos cores
                                que a imagem possui.*/
public:
    BitMapHeader();
    BitMapHeader(const BitMapHeader& orig);
    virtual ~BitMapHeader();
    unsigned short GetBiBitCount() const;
    unsigned int GetBiClrImport() const;
    unsigned int GetBiCompress() const;
    unsigned int GetBiCrlUsed() const;
    unsigned int GetBiHeigth() const;
    unsigned short GetBiPlanes() const;
    unsigned int GetBiSize() const;
    unsigned int GetBiWidth() const;
    unsigned int GetBiXPPMeter() const;
    unsigned int GetBiYPPMeter() const;
    unsigned int GetBiSizeImage() const;
    void SetBiBitCount(unsigned short BiBitCount);
    void SetBiClrImport(unsigned int BiClrImport);
    void SetBiCompress(unsigned int BiCompress);
    void SetBiCrlUsed(unsigned int BiCrlUsed);
    void SetBiHeigth(unsigned int BiHeigth);
    void SetBiPlanes(unsigned short BiPlanes);
    void SetBiSize(unsigned int BiSize);
    void SetBiWidth(unsigned int BiWidth);
    void SetBiXPPMeter(unsigned int BiXPPMeter);
    void SetBiYPPMeter(unsigned int BiYPPMeter);
    void SetBiSizeImage(unsigned int BiZizeImage);
    void SaveBitMapHeader(std::ofstream& arquivoSaida);

    BitMapHeader &operator =(const BitMapHeader &ori);
    
    void read(std::ifstream *input);
    void print();
};

#endif	/* BITMAPHEADER_H */

