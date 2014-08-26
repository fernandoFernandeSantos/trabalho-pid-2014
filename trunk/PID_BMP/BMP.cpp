﻿/* 
 * File:   BMP.cpp
 * Author: fernandofernandes
 *
 * Created on 9 de Abril de 2014, 18:19
 */

#include "BMP.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <cstdio>

#define SATURATION(a,b) ((a < 0) ? b = 0:((a > 255) ? b = 255:b = a));

BMP::BMP() {
}

BMP::BMP(const BMP& orig) {
    this->cabecalhoBitMap = orig.cabecalhoBitMap;
    this->cabecalhoImagem = orig.cabecalhoImagem;
    this->matrizPixels = orig.matrizPixels;
    for (int i = 0; i < 256; i++) {
        this->paletaCores[i] = orig.paletaCores[i];
    }
}

BMP::BMP(const Header& headerOrig, const BitMapHeader& bitMapOrig, const Matriz<Pixel>& matOrig){
    this->cabecalhoImagem = headerOrig;
    this->cabecalhoBitMap = bitMapOrig;
    this->matrizPixels = matOrig;
}

BMP::BMP(const Header& headerOrig, const BitMapHeader& bitMapOrig, 
        const Matriz<Pixel>& matOrig, const CollorPallet *nova){
    this->cabecalhoImagem = headerOrig;
    this->cabecalhoBitMap = bitMapOrig;
    this->matrizPixels = matOrig;
    this->paletaCores = new CollorPallet[256]();
    for (int i = 0; i < 256; i++) {
        this->paletaCores[i] = nova[i];
    }
}

BMP::~BMP() {
    //deletar paleta de cores
    if (this->cabecalhoBitMap.GetBiBitCount() == 8) {
        delete[] this->paletaCores;
        this->paletaCores = NULL;
    }
}

BitMapHeader BMP::GetCabecalhoBitMap() const {
    return cabecalhoBitMap;
}

void BMP::SetCabecalhoBitMap(BitMapHeader cabecalhoBitMap) {
    this->cabecalhoBitMap = cabecalhoBitMap;
}

Header BMP::GetCabecalhoImagem() const {
    return cabecalhoImagem;
}

void BMP::SetCabecalhoImagen(Header cabecalhoImagem) {
    this->cabecalhoImagem = cabecalhoImagem;
}

CollorPallet* BMP::GetPaletaCores() const {
    return paletaCores;
}

void BMP::SetPaletaCores(CollorPallet* paletaCores) {
    this->paletaCores = paletaCores;
}

Matriz<Pixel> BMP::GetMatrizPixels() const {
    return matrizPixels;
}

Matriz<uint> BMP::GetHistogram() const{
    return this->Histograma;
}

void BMP::SetMatrizPixels(Matriz<Pixel> matrizPixels) {
    this->matrizPixels = matrizPixels;
}

void BMP::read(std::ifstream* input) {
    this->cabecalhoImagem.read(input);
    this->cabecalhoBitMap.read(input);
    //verifica se tem mapa de cores

    if (this->cabecalhoBitMap.GetBiBitCount() == 8) { //tem mapa de cores
        int tamanho = (int) pow(2, this->cabecalhoBitMap.GetBiBitCount());
        this->paletaCores = new CollorPallet[tamanho];
        //lê a paleta de cores
        u_char r, g, b, t;
        for (int i = 0; i < tamanho; i++) {
            input->read((char*) & b, sizeof (u_char));
            input->read((char*) & g, sizeof (u_char));
            input->read((char*) & r, sizeof (u_char));
            input->read((char*) & t, sizeof (u_char));

            this->paletaCores[i].setCor(r, g, b, t);


        }
    }

    //aloca matriz de pixels
    this->matrizPixels.mAlloc(this->cabecalhoBitMap.GetBiHeigth(), this->cabecalhoBitMap.GetBiWidth());
    //tamanho imagem
    uint lixo = (this->cabecalhoBitMap.GetBiWidth()) % 4;
    u_char aux;
    //lê o arquivo para 8 bits
    if (this->cabecalhoBitMap.GetBiBitCount() == 8) {
        u_char elemento;
        uint linha = 0, coluna = 0;
        uint aux = 0;
        while (true) {
            input->read((char*) & elemento, sizeof (u_char));
            Pixel p(this->paletaCores[elemento].GetRed(),
                    this->paletaCores[elemento].GetGreen(),
                    this->paletaCores[elemento].GetBlue());
            this->matrizPixels.set(linha, coluna, p);
            coluna++;
            if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                for (uint i = 0; i < lixo * 3; i++) {
                    input->read((char*) &aux, sizeof (u_char));
                }
                linha++;
                coluna = 0;
                if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                    break;
                }
            }
        }
    }
    //lê o arquivo para 24 bits
    if (this->cabecalhoBitMap.GetBiBitCount() == 24) {
        u_char r, g, b;
        uint linha = 0, coluna = 0;
        while (true) {
            input->read((char*) & b, sizeof (u_char));
            input->read((char*) & g, sizeof (u_char));
            input->read((char*) & r, sizeof (u_char));
            Pixel p(r, g, b);
            this->matrizPixels.set(linha, coluna, p);
            coluna++;

            if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                for (uint i = 0; i < lixo; i++) {
                    input->read((char*) &aux, sizeof (u_char));

                }
                linha++;
                coluna = 0;
                if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                    break;
                }
            }
        }
    }
}

void BMP::mallocHistogram(){
    //aloca a variavel Histograma
    //index 0 = R, 1 = G, 2 = B
    this->Histograma.mAlloc(3, (this->GetCabecalhoBitMap().GetBiCrlUsed() == 0)
                            ? 256 : this->GetCabecalhoBitMap().GetBiCrlUsed());
    this->Histograma.fill(0);
}

bool BMP::makeHistogram(){
    if(this->matrizPixels.isEmpty()){
        return false;
    }else{
        mallocHistogram();
        u_char r, g, b;
        Matriz<Pixel> aux(this->GetMatrizPixels());
        for (uint i = 0; i < aux.getLinha(); i++) {
            for (uint j = 0; j < aux.getColuna();j++) {
                r = aux.get(i, j).GetR();
                g = aux.get(i, j).GetG();
                b = aux.get(i, j).GetB();
                this->Histograma.set(0, r, this->Histograma.get(0, r) + 1);
                this->Histograma.set(1, g, this->Histograma.get(1, g) + 1);
                this->Histograma.set(2, b, this->Histograma.get(2, b) + 1);
            }

        }
    }
    return true;
}


long double* BMP::valorMedio() {
    u_int64_t somaR = 0;
    u_int64_t somaG = 0;
    u_int64_t somaB = 0;
    uint altura = this->cabecalhoBitMap.GetBiHeigth();
    uint largura = this->cabecalhoBitMap.GetBiWidth();
    long double divisor = altura * largura;
    u_char r, g, b;
    for (uint i = 0; i < this->cabecalhoBitMap.GetBiHeigth(); i++) {
        for (uint j = 0; j < this->cabecalhoBitMap.GetBiWidth(); j++) {
            r = (this->matrizPixels.get(i, j).GetR());
            g = (this->matrizPixels.get(i, j).GetG());
            b = (this->matrizPixels.get(i, j).GetB());
            somaR += r;
            somaG += g;
            somaB += b;
        }
    }
    long double *valores;
    valores = new long double[3];
    valores[0] = somaR / divisor;

    valores[1] = somaG / divisor;

    valores[2] = somaB / divisor;

    return valores;
}

bool BMP::salvar(const char* nomeArquivo) {
    try {
        std::ofstream arquivoSaida(nomeArquivo, std::ios::out);
        //verifica se pode ser aberto ou não
        if (arquivoSaida.is_open() && arquivoSaida.good()) {
            this->cabecalhoImagem.saveHeader(arquivoSaida);
            this->cabecalhoBitMap.SaveBitMapHeader(arquivoSaida);
            u_char aux;
            //se tem paleta de cores grava a paleta e a matriz
            if (this->cabecalhoBitMap.GetBiBitCount() == 8) {
                uint lixo = (this->cabecalhoBitMap.GetBiWidth() * 3) % 4;
                u_char r, g, b, t;
                for (int i = 0; i < 256; i++) {
                    b = this->paletaCores[i].GetBlue();
                    g = this->paletaCores[i].GetGreen();
                    r = this->paletaCores[i].GetRed();
                    t = this->paletaCores[i].GetReservado();

                    arquivoSaida.write((char*) & b, sizeof (u_char));
                    arquivoSaida.write((char*) & g, sizeof (u_char));
                    arquivoSaida.write((char*) & r, sizeof (u_char));
                    arquivoSaida.write((char*) & t, sizeof (u_char));
                }

                //grava a matriz para 8 bits
                Pixel p;
                uint linha = 0, coluna = 0;
                while (true) {
                    try {
                        p = this->matrizPixels.get(linha, coluna);
                        u_char indice = this->findIndex(p.GetR(), p.GetG(), p.GetB());
                        arquivoSaida.write((char*) & indice, sizeof (u_char));
                        coluna++;
                        if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                            linha++;
                            for (uint i = 0; i < lixo; i++) {
                                arquivoSaida.write((char*) & aux, sizeof (u_char));
                            }
                            coluna = 0;
                            if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                                break;
                            }
                        }
                    } catch (std::exception& ex) {
                        std::cout << ex.what();
                        break;
                    }
                }
            }
            //grava para 24 bits
            if (this->cabecalhoBitMap.GetBiBitCount() == 24) {
                u_char r, g, b;
                uint linha = 0, coluna = 0;
                uint lixo = (this->cabecalhoBitMap.GetBiWidth()) % 4;
                while (true) {
                    r = this->matrizPixels.get(linha, coluna).GetR();
                    g = this->matrizPixels.get(linha, coluna).GetG();
                    b = this->matrizPixels.get(linha, coluna).GetB();
                    arquivoSaida.write((char*) & b, sizeof (u_char));
                    arquivoSaida.write((char*) & g, sizeof (u_char));
                    arquivoSaida.write((char*) & r, sizeof (u_char));
                    coluna++;
                    if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                        linha++;
                        for (uint i = 0; i < lixo; i++) {
                            arquivoSaida.write((char*) & aux, sizeof (u_char));

                        }
                        coluna = 0;
                        if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                            break;
                        }
                    }

                }
            }
            arquivoSaida.close();
        } else {
            std::cout << "Não foi possível abrir este arquivo\n";
            return false;
        }
    } catch (std::exception& e) {
        std::cout << "Pau em algum lugar\n";
        return false;
    }
    return true;
}

u_char BMP::findIndex(u_char r, u_char g, u_char b) {
    int tamanho = (int) pow(2, this->cabecalhoBitMap.GetBiBitCount());
    for (u_char i = 0; i < tamanho; i++) {
        if ((r == this->paletaCores[i].GetRed())
                && (g == this->paletaCores[i].GetGreen())
                && (b == this->paletaCores[i].GetBlue())) {
            return i;
        }
    }
    return 0;
}

long double * BMP::variancia(long double * valorMedio) {
    u_int64_t somaR = 0;
    u_int64_t somaG = 0;
    u_int64_t somaB = 0;
    u_int64_t divisor = this->cabecalhoBitMap.GetBiHeigth() * this->cabecalhoBitMap.GetBiWidth();
    for (uint i = 0; i < this->cabecalhoBitMap.GetBiHeigth(); i++) {
        for (uint j = 0; j < this->cabecalhoBitMap.GetBiWidth(); j++) {
            somaR += pow(((int) (this->matrizPixels.get(i, j).GetR()) - valorMedio[0]), 2);
            somaG += pow(((int) (this->matrizPixels.get(i, j).GetG()) - valorMedio[1]), 2);
            somaB += pow(((int) (this->matrizPixels.get(i, j).GetB()) - valorMedio[2]), 2);
        }
    }
    long double *valores;
    valores = new long double[3];
    valores[0] = somaR / divisor;

    valores[1] = somaG / divisor;

    valores[2] = somaB / divisor;

    return valores;

}

long double * BMP::covariancia(BMP g2) {
    u_char rThis, gThis, bThis;
    u_char rG2, gG2, bG2;
    int64_t somaR = 0;
    int64_t somaG = 0;
    int64_t somaB = 0;
    //vou pegar as dimensões da menor imagem
    unsigned long int altura = (this->cabecalhoBitMap.GetBiHeigth() < g2.cabecalhoBitMap.GetBiHeigth()) ?
                this->cabecalhoBitMap.GetBiHeigth() : g2.cabecalhoBitMap.GetBiHeigth();
    unsigned long int largura = (this->cabecalhoBitMap.GetBiWidth() < g2.cabecalhoBitMap.GetBiWidth()) ?
                this->cabecalhoBitMap.GetBiWidth() : g2.cabecalhoBitMap.GetBiWidth();
    //pega as médias
    long double *valorMedioThis = this->valorMedio();
    long double *valorMedioG2 = g2.valorMedio();

    int64_t divisor = altura * largura;
    for (uint i = 0; i < altura; i++) {
        for (uint j = 0; j < largura; j++) {
            rThis = (this->matrizPixels.get(i, j).GetR() - valorMedioThis[0]);
            gThis = (this->matrizPixels.get(i, j).GetG() - valorMedioThis[1]);
            bThis = (this->matrizPixels.get(i, j).GetB() - valorMedioThis[2]);

            rG2 = g2.matrizPixels.get(i, j).GetR() - valorMedioG2[0];
            gG2 = g2.matrizPixels.get(i, j).GetG() - valorMedioG2[1];
            bG2 = g2.matrizPixels.get(i, j).GetB() - valorMedioG2[2];

            somaR += rThis * rG2;
            somaG += gThis * gG2;
            somaB += bThis * bG2;
        }

    }
    long double *valores;
    valores = new long double[3];
    valores[0] = somaR / divisor;

    valores[1] = somaG / divisor;

    valores[2] = somaB / divisor;

    return valores;
}

void BMP::printCabecalhoArquivo(){
    this->cabecalhoImagem.print();
}

void BMP::printCabecalhoImagem(){
    this->cabecalhoBitMap.print();
}

void BMP::limiarImagem(u_int32_t fator){
    u_int32_t k = 0;
    uint lin = this->matrizPixels.getLinha();
    uint col = this->matrizPixels.getColuna();
    Pixel p;
    for (uint i = 0; i < lin; i++) {
        for (uint j = 0; j < col; j++) {
            k = this->matrizPixels.get(i , j).GetB() +
                    this->matrizPixels.get(i , j).GetG() +
                    this->matrizPixels.get(i , j).GetR();
            k /=3;
            if(k > fator){
                p.setRGB(255,255,255);
                this->matrizPixels.set(i, j,p );
            }else{
                p.setRGB(0,0,0);
                this->matrizPixels.set(i, j,p );
            }
        }
    }
}
//1 = &; 2 = |, 3 = +, 4 = -, 5 = ~
bool BMP::operations(const BMP& g2, u_char operacao){
    
    Matriz<Pixel> matAux(g2.GetMatrizPixels());
    uint lin = (this->matrizPixels.getLinha() < matAux.getLinha() ?
                    this->matrizPixels.getLinha(): matAux.getLinha());
    uint col = (this->matrizPixels.getColuna() < matAux.getColuna() ?
                    this->matrizPixels.getColuna(): matAux.getColuna());

    Pixel p, b;
    if(operacao == 1){ // &
        for (uint i = 0; i < lin; i++) {
            for (uint j = 0; j < col; j++) {
                p = this->matrizPixels.get(i,j);
                b = matAux.get(i,j);
                p = p & b;
                this->matrizPixels.set(i, j, p);
            }
        }
    }
    if(operacao == 2){ // |
        for (uint i = 0; i < lin; i++) {
            for (uint j = 0; j < col; j++) {
                p = this->matrizPixels.get(i,j);
                b = matAux.get(i,j);
                p = p | b;
                this->matrizPixels.set(i, j, p);
            }
        }
    }
    if(operacao == 3){ // +
        for (uint i = 0; i < lin; i++) {
            for (uint j = 0; j < col; j++) {
                p = this->matrizPixels.get(i,j);
                b = matAux.get(i,j);
                p = p + b;
                this->matrizPixels.set(i, j, p);
            }
        }
    }
    if(operacao == 4){ //-
        for (uint i = 0; i < lin; i++) {
            for (uint j = 0; j < col; j++) {
                p = this->matrizPixels.get(i,j);
                b = matAux.get(i,j);
                p = p - b;
                this->matrizPixels.set(i, j, p);
            }
        }
    }
    if(operacao == 5){ //~
        for (uint i = 0; i < lin; i++) {
            for (uint j = 0; j < col; j++) {
                p = this->matrizPixels.get(i,j);
                ~p;
                this->matrizPixels.set(i, j, p);
            }
        }
    }
    return true;
}

BMP BMP::imageToGray(){   
    //novos objetos
    Header novoHe;
    BitMapHeader novoBitHe;
    CollorPallet *novaPallet = new CollorPallet[256]();
    
    uint lin = this->matrizPixels.getLinha();
    uint col = this->matrizPixels.getColuna();
    Matriz<Pixel> novaMat(lin, col);
    
    for (int i = 0; i < 256; i++) {
        novaPallet[i].setCor((u_char)i, (u_char)i, (u_char)i, (u_char)0);
    }
    unsigned char* BfType = new unsigned char[3];
    BfType[0] = 'B';
    BfType[1] = 'M';
    novoHe.SetBfType(BfType);
    novoHe.SetBfSize(lin * col + 1078);
    novoHe.SetBfReser1(0);
    novoHe.SetBfReser2(0);
    novoHe.SetBfOffSetBits(1078); //agora tem paleta
    
    //seta as definições do bitmap header
    novoBitHe.SetBiBitCount(8);
    novoBitHe.SetBiClrImport(256);
    novoBitHe.SetBiCompress(0);
    novoBitHe.SetBiCrlUsed(0);
    novoBitHe.SetBiHeigth(lin);
    novoBitHe.SetBiPlanes(1);
    novoBitHe.SetBiSize(40);
    novoBitHe.SetBiWidth(col);
    novoBitHe.SetBiXPPMeter(this->cabecalhoBitMap.GetBiXPPMeter());
    novoBitHe.SetBiYPPMeter(this->cabecalhoBitMap.GetBiYPPMeter());
    novoBitHe.SetBiSizeImage(0);
    
    Pixel p;
    for (uint i = 0; i < lin; i++) {
        for (uint j = 0; j < col; j++) {
            p =  this->matrizPixels.get(i,j);
            p = p / 3;
            novaMat.set(i,j, p);
        }
    }
    BMP results(novoHe, novoBitHe, novaMat, novaPallet);
    delete [] novaPallet;
    return results;
}

///convolução da imagem
/// recebe mascara de floats
void BMP::convolution(Matriz<double> &mask){
    Matriz<Pixel>  tempMat(this->GetMatrizPixels());
    long int maskCenterX, maskCenterY,
            maskRows, maskCols, rows, cols,ii, jj;
    long int nn, mm;

    maskCols = mask.getColuna();
    maskRows = mask.getLinha();
    rows = tempMat.getLinha();
    cols = tempMat.getColuna();

    Matriz<double> outRed(rows, cols);
    Matriz<double> outGre(rows, cols);
    Matriz<double> outBlu(rows, cols);

    outRed.fill(0);
    outBlu.fill(0);
    outGre.fill(0);

    maskCenterX = maskCols / 2;
    maskCenterY = maskRows / 2;

    double r = 0, g = 0, b = 0;
    Pixel p;
    for(long int i=0; i < rows; ++i)              // rows
    {
        for(long int j=0; j < cols; ++j)          // columns
        {
            for(long int m=0; m < maskRows; ++m)     // kernel rows
            {
                mm = maskRows - 1 - m;      // row index of flipped kernel

                for(long int n=0; n < maskCols; ++n) // kernel columns
                {
                    nn = maskCols - 1 - n;  // column index of flipped kernel

                    // index of input signal, used for checking boundary
                    ii = i + (m - maskCenterY);
                    jj = j + (n - maskCenterX);

                    // ignore input samples which are out of bound

                    if( ii >= 0 && ii < rows && jj >= 0 && jj < cols ){
                        //matriz original
                        p =  tempMat.get(ii,jj);
                        r = p.GetR() * mask.get(mm, nn);
                        g = p.GetG() * mask.get(mm, nn);
                        b = p.GetG() * mask.get(mm, nn);

                        outRed.set(i, j, (outRed.get(i,j) + r));
                        outGre.set(i, j, (outGre.get(i,j) + g));
                        outBlu.set(i, j, (outBlu.get(i,j) + b));
                    }
                }
            }
        }
    }
    //junto os resultados
    int R, G, B;
    for(long int i = 0; i < rows; i++){
        for(long int j = 0; j < cols; j++){
            R = outRed.get(i,j);
            G = outGre.get(i,j);
            B = outBlu.get(i,j);
            SATURATION(R,R);
            SATURATION(G,G);
            SATURATION(B,B);
            p.setRGB(R,G,B);
            tempMat.set(i,j, p);
        }
    }
    this->matrizPixels = tempMat;
}

void BMP::convolucao(Matriz<double> &orig){
    this->convolution(orig);
}

void BMP::sobel(bool pos){
    Matriz<double> aux(3,3);
    if(pos){ //verdadeiro vertical, falso horizontal
        aux.set(0,0, 1.0/4.0); aux.set(0,1, 0); aux.set(0, 2, -1.0/4.0);
        aux.set(1,0, 2.0/4.0); aux.set(1,1, 0); aux.set(1,2, -2.0/4.0);
        aux.set(2,0, 1.0/4.0); aux.set(2,1, 0); aux.set(2,2, -1.0/4.0);
    }else{
        aux.set(0,0, -1.0/4); aux.set(0,1, -2.0/4.0); aux.set(0, 2, -1.0/4.0);
        aux.set(1,0, 0); aux.set(1,1, 0); aux.set(1,2, 0);
        aux.set(2,0, 1.0/4.0); aux.set(2,1, 2.0/4.0); aux.set(2,2, 1.0/4.0);
    }
    this->convolution(aux);
}

void BMP::media(uint ordem){
    Matriz<double> aux(ordem, ordem);
    float t = 1.0/(ordem*ordem);
    aux.fill(t);
    this->convolution(aux);
}

void BMP::mediana(uint ordem){
    Vetor<u_char> *maskOrdered;
    Matriz<Pixel> mask(ordem, ordem);
    Matriz<Pixel>  tempMat(this->GetMatrizPixels());
    long int maskCenterX, maskCenterY,
            maskRows, maskCols, rows, cols,ii, jj;
    uint midle = (ordem * ordem) /2;

    maskCols = ordem;
    maskRows = ordem;
    rows = tempMat.getLinha();
    cols = tempMat.getColuna();

    maskCenterX = maskCols / 2;
    maskCenterY = maskRows / 2;

    u_char r = 0, g = 0, b = 0;
    Pixel p;
    for(long int i=0; i < rows; ++i)              // rows
    {
        for(long int j=0; j < cols; ++j)          // columns
        {
            for(long int m=0; m < maskRows; ++m)     // kernel rows
            {
                for(long int n=0; n < maskCols; ++n) // kernel columns
                {
                    ii = i + m - maskCenterX;
                    jj = j + n - maskCenterY;
                    if((ii < 0) || (jj < 0) || (ii >= rows) || (jj >= cols)){
                        //cima
                        if(ii < 0){
                            ii = i + m;
                        }
                        //baixo
                        if(ii >= rows){
                            ii = i - m;
                        }
                        //lado esquerdo
                        if(jj < 0){
                            jj = j + n;
                        }
                        //lado direito
                        if(jj >= cols){
                            jj = j - n;
                        }
                    }
                    p =  tempMat.get(ii,jj);
                    mask.set(m,n, p);
                }
            }
            maskOrdered = this->maskOrder(mask);
            r = maskOrdered[0][midle];
            g = maskOrdered[1][midle];
            b = maskOrdered[2][midle];
            p.setRGB(r, g, b);
            tempMat.set(i, j, p);

            delete [] maskOrdered[0].getVetor();
            delete [] maskOrdered[1].getVetor();
            delete [] maskOrdered[2].getVetor();
        }
    }
    this->matrizPixels = tempMat;
}

void BMP::roberts(bool pos){
    Matriz<double> aux(3,3);
    if(pos){ //verdadeiro vertical, falso horizontal
        aux.fill(0);
        aux.set(1,1, 1); aux.set(0,2, -1);
    }else{
        aux.fill(0);
        aux.set(1,1, 1); aux.set(0,0, -1);
    }
    this->convolution(aux);
}

Matriz<uint> BMP::transformationFunction(){
    if(!this->makeHistogram())
        return NULL;
    
    Matriz<uint> soma(this->Histograma.getLinha(), this->Histograma.getColuna());

    soma.fill(0);
    long long int acumuladorR = 0;
    long long int acumuladorG = 0;
    long long int acumuladorB = 0;

    //escala
    float scale = 255.0f / (float) (this->matrizPixels.getColuna() * this->matrizPixels.getLinha());

    for (uint i = 0; i < this->Histograma.getColuna(); ++i) {
        acumuladorR += this->Histograma.get(0, i);
        acumuladorG += this->Histograma.get(1, i);
        acumuladorB += this->Histograma.get(2, i);
        //coloca na matriz soma a função de probabilidades
        soma.set(0, i, (uint) (acumuladorR * scale));
        soma.set(1, i, (uint) (acumuladorG * scale));
        soma.set(2, i, (uint) (acumuladorB * scale));
    }
    return soma;
}

bool BMP::histogramEqualizer(){
    Matriz<uint> tabelaConsulta = this->transformationFunction();
    if(tabelaConsulta.isEmpty())
        return false;
    Matriz<Pixel> resultado(this->matrizPixels.getLinha(),
                            this->matrizPixels.getColuna());
    uint tempR = 0;
    uint tempG = 0;
    uint tempB = 0;
    Pixel p;
    for (uint i = 0; i < this->matrizPixels.getLinha(); ++i) {
        for (uint j = 0; j < this->matrizPixels.getColuna(); ++j) {
            p = this->matrizPixels.get(i,j);
            tempR = tabelaConsulta.get(0, p.GetR());
            tempG = tabelaConsulta.get(1, p.GetG());
            tempB = tabelaConsulta.get(2, p.GetB());
            p.setRGB(tempR, tempG, tempB);
            resultado.set(i, j, p);
        }
    }

    this->matrizPixels = resultado;
    return true;
}

Vetor<u_char>* BMP::maskOrder(Matriz<Pixel> &orig){
    uint size = orig.getColuna() * orig.getLinha();
    Vetor<u_char> *ret;
    ret = new Vetor<u_char>[3];
    if(ret == NULL)
        return NULL;
    for (int i = 0; i < 3; ++i) {
        ret[i] =  Vetor<u_char>(size);
    }
    uint k = 0;
    Pixel p;
    //coloca nos vetores a matriz
    for (uint i = 0; i < orig.getLinha(); ++i) {
        for (uint j = 0; j < orig.getColuna(); ++j) {
            p = orig.get(i, j);
            ret[0][k] = p.GetR();
            ret[1][k] = p.GetG();
            ret[2][k++] = p.GetB();
        }
    }

    //ordena os vetores da mascara
    ret[0].mergeSort(ret[0].getVetor(), size);
    ret[1].mergeSort(ret[1].getVetor(), size);
    ret[2].mergeSort(ret[2].getVetor(), size);
    return ret;
}

void BMP::printHistogram(bool fifthShades){
    if(this->Histograma.isEmpty())
        return;
    Header newHeader(this->GetCabecalhoImagem());
    //nova imagem sem paleta
    newHeader.SetBfOffSetBits(54);
    //novo tamanho
    uint altura = 0;
    uint largura = 1024;
    for (int i = 0; i < this->Histograma.getColuna(); i++) {
        if(altura < this->Histograma.get(0, i))
            altura = this->Histograma.get(0, i);

        if(altura < this->Histograma.get(1, i))
            altura = this->Histograma.get(1, i);

        if(altura < this->Histograma.get(2, i))
            altura = this->Histograma.get(2, i);
    }
    uint proporcao = 2;
    altura = (altura ) / 10;
    newHeader.SetBfSize((largura * altura) + 54);

    BitMapHeader newBitMapReader;
    newBitMapReader.SetBiSize(40);
    newBitMapReader.SetBiWidth(largura);

    newBitMapReader.SetBiHeigth(altura);
    newBitMapReader.SetBiPlanes(1);
    newBitMapReader.SetBiBitCount(24);
    newBitMapReader.SetBiCompress(0);
    newBitMapReader.SetBiSizeImage((altura * largura));
    newBitMapReader.SetBiXPPMeter(0);
    newBitMapReader.SetBiYPPMeter(0);
    newBitMapReader.SetBiCrlUsed(0);
    newBitMapReader.SetBiClrImport(0);

    Matriz<Pixel> outR(altura, largura), outG(altura, largura), outB(altura, largura);

    uint histR, histG, histB;
    Pixel pRed(255, 0, 0), pGreen(0, 255, 0), pBlue(0, 0, 255);
    Pixel pGray(255, 255, 255);
    uint incremento = (largura / 256);

    for(uint i = 0; i < altura; i++){
        for(uint j = 0, jHist = 0; j < largura, jHist < 256; j += incremento, jHist++){
            if(!fifthShades){
                histR = this->Histograma.get(0,jHist);
                histG = this->Histograma.get(1,jHist);
                histB = this->Histograma.get(2,jHist);

                histR = (histR * proporcao) / 10;
                histG = (histG * proporcao) / 10;
                histB = (histB * proporcao) / 10;
                //verifica a intensidade para pintar para cada pixel
                //para componente R
                if(histR > i){
                    //for para fazer a proporção
                    for(uint k = 0; k < incremento; k++){
                        outR.set(i, (j + k), pRed);
                    }
                }

                //para componente G
                if(histG > i){
                    //for para fazer a proporção
                    for(uint k = 0; k < incremento; k++){
                        outG.set(i, (j + k), pGreen);
                    }
                }

                //para componente B
                if(histB > i){
                    //for para fazer a proporção
                    for(uint k = 0; k < incremento; k++){
                        outB.set(i, (j + k), pBlue);
                    }
                }
            }else{ //gera só um histograma para cinza
                histR = this->Histograma.get(0,jHist);
                histR = (histR * proporcao) / 10;
                if(histR > i){
                    //for para fazer a proporção
                    for(uint k = 0; k < incremento; k++){
                        outR.set(i, (j + k), pGray);
                    }
                }
            }
        }
    }
    if(fifthShades){
        BMP novoR(newHeader, newBitMapReader, outR);
        novoR.salvar("histogram.bmp");
    }else{
        BMP novoR(newHeader, newBitMapReader, outR);
        novoR.salvar("histogramRED.bmp");
        BMP novoG(newHeader, newBitMapReader, outG);
        BMP novoB(newHeader, newBitMapReader, outB);
        novoG.salvar("histogramaGreen.bmp");
        novoB.salvar("histogramaBlue.bmp");
    }
}

