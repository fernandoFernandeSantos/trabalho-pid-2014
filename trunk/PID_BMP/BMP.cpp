/* 
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

BMP::BMP() {
}

BMP::BMP(const BMP& orig) {
    this->cabecalhoBitMap = orig.cabecalhoBitMap;
    this->cabecalhoImagem = orig.cabecalhoImagem;
    this->matrizPixels = orig.matrizPixels;
    this->paletaCores = orig.paletaCores;
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

Matriz<int> BMP::GetHistogram() const{
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
        cout << aux;
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
            //como em c só grava endereço tem que por para variavéis
            char BfType1 = this->cabecalhoImagem.GetBfType()[0];
            char BfType2 = this->cabecalhoImagem.GetBfType()[1];
            uint BfSize = this->cabecalhoImagem.GetBfSize();
            u_short BfReser1 = this->cabecalhoImagem.GetBfReser1();
            u_short BfReser2 = this->cabecalhoImagem.GetBfReser2();
            uint BfOffSetBits = this->cabecalhoImagem.GetBfOffSetBits();
            uint BiSize = this->cabecalhoBitMap.GetBiSize();
            uint BiWidth = this->cabecalhoBitMap.GetBiWidth();
            uint BiHeigth = this->cabecalhoBitMap.GetBiHeigth();
            u_short BiPlanes = this->cabecalhoBitMap.GetBiPlanes();
            u_short BiBitCount = this->cabecalhoBitMap.GetBiBitCount();
            uint BiCompress = this->cabecalhoBitMap.GetBiCompress();
            uint BiSizeImage = this->cabecalhoBitMap.GetBiSizeImage();
            uint BiXPPMeter = this->cabecalhoBitMap.GetBiXPPMeter();
            uint BiYPPMeter = this->cabecalhoBitMap.GetBiYPPMeter();
            uint BiCrlUsed = this->cabecalhoBitMap.GetBiCrlUsed();
            uint BiClrImport = this->cabecalhoBitMap.GetBiClrImport();

            //grava o header
            arquivoSaida.write((char*) & BfType1, sizeof (BfType1));
            arquivoSaida.write((char*) & BfType2, sizeof (BfType2));
            arquivoSaida.write((char*) & BfSize, sizeof (BfSize));
            arquivoSaida.write((char*) & BfReser1, sizeof (BfReser1));
            arquivoSaida.write((char*) & BfReser2, sizeof (BfReser2));
            arquivoSaida.write((char*) & BfOffSetBits, sizeof (BfOffSetBits));

            //grava o cabeçalho da imagem
            arquivoSaida.write((char*) & BiSize, sizeof (BiSize));
            arquivoSaida.write((char*) & BiWidth, sizeof (BiWidth));
            arquivoSaida.write((char*) & BiHeigth, sizeof (BiHeigth));
            arquivoSaida.write((char*) & BiPlanes, sizeof (BiPlanes));
            arquivoSaida.write((char*) & BiBitCount, sizeof (BiBitCount));
            arquivoSaida.write((char*) & BiCompress, sizeof (BiCompress));
            arquivoSaida.write((char*) & BiSizeImage, sizeof (BiSizeImage));
            arquivoSaida.write((char*) & BiXPPMeter, sizeof (BiXPPMeter));
            arquivoSaida.write((char*) & BiYPPMeter, sizeof (BiYPPMeter));
            arquivoSaida.write((char*) & BiCrlUsed, sizeof (BiCrlUsed));
            arquivoSaida.write((char*) & BiClrImport, sizeof (BiClrImport));

            uint lixo = (this->cabecalhoBitMap.GetBiWidth()) % 4;
            u_char aux;
            //se tem paleta de cores grava a paleta e a matriz
            if (this->cabecalhoBitMap.GetBiBitCount() == 8) {
                u_char r, g, b, t;
                int tamanho = (int) pow(2, this->cabecalhoBitMap.GetBiBitCount());
                for (int i = 0; i < tamanho; i++) {
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
                uint linha = 0, coluna = 0;
                while (true) {
                    try {
                        u_char indice = this->findIndex(this->matrizPixels.get(linha, coluna).GetR(),
                                                        this->matrizPixels.get(linha, coluna).GetG(),
                                                        this->matrizPixels.get(linha, coluna).GetB());
                        arquivoSaida.write((char*) & indice, sizeof (u_char));
                        coluna++;
                        if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                            linha++;
                            for (uint i = 0; i < lixo * 3; i++) {
                                arquivoSaida.write((char*) & aux, sizeof (u_char));

                            }
                            coluna = 0;
                            if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                                break;
                            }
                        }
                    } catch (std::exception& ex) {
                        std::cout << "Pau na gravação";
                        break;
                    }
                }
            }
            //grava para 24 bits
            if (this->cabecalhoBitMap.GetBiBitCount() == 24) {
                u_char r, g, b;
                uint linha = 0, coluna = 0;
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
    uint lin = this->matrizPixels.getLinha();
    uint col = this->matrizPixels.getColuna();
    if(g2.GetCabecalhoBitMap().GetBiHeigth() != lin || g2.GetCabecalhoBitMap().GetBiWidth() != col)
        return false;

    Matriz<Pixel> matAux(g2.GetMatrizPixels());
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

void BMP::imageToGray(){
    //mudando as configurações do header
    Header he(this->GetCabecalhoImagem());
    he.SetBfOffSetBits(1078);
    this->SetCabecalhoImagen(he);

    //mudando as configurações do bimapheader
    BitMapHeader bitMH(this->GetCabecalhoBitMap());
    bitMH.SetBiBitCount(8);
    bitMH.SetBiCrlUsed(256);
    this->SetCabecalhoBitMap(bitMH);

    uint lin = this->matrizPixels.getLinha();
    uint col = this->matrizPixels.getColuna();
    Pixel p;
    this->paletaCores = new CollorPallet[256];
    for (uint i = 0; i < lin; i++) {
        for (uint j = 0; j < col; j++) {
            p = this->matrizPixels.get(i,j);
            p = p / 3;
            this->matrizPixels.set(i, j, p);
            this->paletaCores[p.GetB()].setCor(p.GetR(), p.GetG(),
                                               p.GetB(), 0);
        }

    }
}

