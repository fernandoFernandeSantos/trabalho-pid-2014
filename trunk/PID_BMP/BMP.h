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
#include "Vetor.h"
#include <vector>
#include "Ponto.h"

#define	BMP_H

typedef vector<unsigned int> IntArray;
typedef vector<IntArray> Image;

class BMP {
public:
    BMP();
    BMP(const BMP& orig);
    BMP(const Header& headerOrig, const BitMapHeader& bitMapOrig, const Matriz<Pixel>& matOrig);
    BMP(const Header& headerOrig, const BitMapHeader& bitMapOrig,
            const Matriz<Pixel>& matOrig, const CollorPallet *nova);
    virtual ~BMP();
    BitMapHeader GetCabecalhoBitMap() const;
    void SetCabecalhoBitMap(BitMapHeader cabecalhoBitMap);
    Header GetCabecalhoImagem() const;
    void SetCabecalhoImagen(Header cabecalhoImagen);
    CollorPallet* GetPaletaCores() const;
    void SetPaletaCores(CollorPallet* paletaCores);
    Matriz<Pixel> GetMatrizPixels() const;
    Matriz<uint> GetHistogram() const;
    void SetMatrizPixels(Matriz<Pixel> matrizPixels);
    void read(std::ifstream *input);
    bool salvar(const char* nomeArquivo);


    //operações
    long double * variancia(long double * valorMedio);
    long double * covariancia(BMP g2);
    long double* valorMedio();
    void printCabecalhoArquivo();
    void printCabecalhoImagem();
    bool makeHistogram();
    void limiarImagem(u_int32_t fator = 127);
    bool operations(const BMP& g2, u_char operacao); //1 = &; 2 = |, 3 = +, 4 = -, 5 = ~
    BMP imageToGray();
    void convolucao(Matriz<double> &orig);
    void sobel();
    void media(uint ordem);
    void mediana(uint ordem);
    void roberts(bool pos);
    bool histogramEqualizer();
    Vetor<u_char>* maskOrder(Matriz<Pixel> &orig);
    void printHistogram(bool fiftyShades);
    //hough
    void houghTransformation(unsigned int min_r, unsigned int max_r);


private:
    CollorPallet *paletaCores; //paleta de cores ou mapa de cores
    BitMapHeader cabecalhoBitMap; //cabeçalho do mapa de bits
    Header cabecalhoImagem; //cabeçalho do arquivo
    //armazena os dados do bmp
    Matriz<Pixel> matrizPixels;
    Matriz<uint> Histograma;

    //métodos privados
    u_char findIndex(unsigned char r, unsigned char g, unsigned char b);
    //aloca o histograma de acordo com a imagem
    void mallocHistogram();
    void convolution(Matriz<double> &mask);
    Matriz<uint> transformationFunction();

    void acumulaCirculo(Image &image, const Ponto point, unsigned int radius);
    void acumulaPixel(Image &image, const Ponto point);
    void desenhaCirculo(Matriz<Pixel> &image, const Ponto point, unsigned int radius, const Pixel &color);
    void desenhaPixel(Matriz<Pixel> &image, const Ponto point, const Pixel &color);
    Matriz<Pixel> sobelPlusLimiar(Matriz<Pixel> &source);
    
    //heuristicas para encontrar o olho
    bool verificaDoisPontos(const Ponto p1, const Ponto p2, unsigned int erro_min, unsigned erro_max);
    bool distanciaEproporcao(const Ponto p1, const Ponto p2);
    
};



#endif	/* BMP_H */

