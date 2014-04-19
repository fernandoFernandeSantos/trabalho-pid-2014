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
}

BMP::~BMP() {
    //deletar paleta de cores
    if (this->paletaCores != NULL) {
        delete[] this->paletaCores;
        this->paletaCores = NULL;
    }
    //deletar a matriz de pixels
    if (this->matrizPixels != NULL) {
        for (int i = 0; i < this->cabecalhoBitMap.GetBiHeigth(); i++) {
            delete[] this->matrizPixels[i];
            this->matrizPixels[i] = NULL;
        }
        delete[] this->matrizPixels;
        this->matrizPixels = NULL;
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

Pixel** BMP::GetMatrizPixels() const {
    return matrizPixels;
}

void BMP::SetMatrizPixels(Pixel** matrizPixels) {
    this->matrizPixels = matrizPixels;
}

void BMP::read(std::ifstream* input) {
    this->cabecalhoImagem.read(input);
    this->cabecalhoBitMap.read(input);
    //verifica se tem mapa de cores

    if (this->cabecalhoBitMap.GetBiCrlUsed() <= 256 && this->cabecalhoBitMap.GetBiCrlUsed()) { //tem mapa de cores
        this->paletaCores = new CollorPallet[(int) this->cabecalhoBitMap.GetBiCrlUsed()];
        //lê a paleta de cores
        unsigned char r, g, b, t;
        for (int i = 0; i < this->cabecalhoBitMap.GetBiCrlUsed(); i++) {
            input->read((char*) & b, sizeof (unsigned char));
            input->read((char*) & g, sizeof (unsigned char));
            input->read((char*) & r, sizeof (unsigned char));
            input->read((char*) & t, sizeof (unsigned char));
            this->paletaCores[i].setCor(r, g, b, t);
        }
    }

    //aloca matriz de pixels
    this->matrizPixels = new Pixel*[this->cabecalhoBitMap.GetBiHeigth()];
    for (int i = 0; i < this->cabecalhoBitMap.GetBiHeigth(); i++) {
        this->matrizPixels[i] = new Pixel[this->cabecalhoBitMap.GetBiWidth()];
    }

    //lê o arquivo para 8 bits
    if (this->cabecalhoBitMap.GetBiBitCount() == 8) {
        unsigned char elemento;
        int linha = 0, coluna = 0;
        while (true) {
            input->read((char*) & elemento, sizeof (unsigned char));
            try {
                char* elementoTrans = new char(elemento);
                int posicao = (int) strtol(elementoTrans, NULL, 16);
                this->matrizPixels[linha][coluna].setRGB(
                        this->paletaCores[posicao].GetRed(),
                        this->paletaCores[posicao].GetGreen(),
                        this->paletaCores[posicao].GetBlue());
                coluna++;
                if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                    linha++;
                    coluna = 0;
                    if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                        break;
                    }
                }
            } catch (std::exception& ex) {
                std::cout << "Pau na conversão";
                break;
            }
        }
    }
    //lê o arquivo para 24 bits
    if (this->cabecalhoBitMap.GetBiBitCount() == 24) {
        unsigned char r, g, b;
        int linha = 0, coluna = 0;
        while (true) {
            input->read((char*) & b, sizeof (unsigned char));
            input->read((char*) & g, sizeof (unsigned char));
            input->read((char*) & r, sizeof (unsigned char));
            this->matrizPixels[linha][coluna].setRGB(r, g, b);
            coluna++;
            if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                linha++;
                coluna = 0;
                if (linha == this->cabecalhoBitMap.GetBiHeigth()) {
                    break;
                }
            }

        }
    }
}

void BMP::printInfo() {
    this->cabecalhoImagem.print();
    this->cabecalhoBitMap.print();
    int numeroCores = this->cabecalhoBitMap.GetBiCrlUsed();
    double* resultado = this->valorMedio();
    for (int i = 0; i < 3; i++) {
        std::cout << resultado[i] << "\n";

    }
    //    if (numeroCores == 16 || numeroCores == 256)
    //        for (int i = 0; i < numeroCores; i++) {
    //            std::cout << "Cor " << i << " Azul " << this->paletaCores[i].GetBlue() << " Vermelho " << this->paletaCores[i].GetRed() 
    //                    << " Verde "  << this->paletaCores[i].GetGreen() << "\n" << " T = " << this->paletaCores[i].GetReservado() << "\n";
    //            
    //        }
    //    for (int i = 0; i < this->cabecalhoBitMap.GetBiHeigth(); i++) {
    //        for (int j = 0; j < this->cabecalhoBitMap.GetBiWidth(); j++) {
    //            std::cout << "Cor Azul = " << this->matrizPixels[i][j].GetB();
    //            std::cout << " Cor Verde = " << this->matrizPixels[i][j].GetG();
    //            std::cout << " Cor Vermelho = " << this->matrizPixels[i][j].GetR() << "\n";
    //        }
    //    }
}

double* BMP::valorMedio() {
    long double somaR = 0;
    long double somaG = 0;
    long double somaB = 0;
    int divisor = this->cabecalhoBitMap.GetBiHeigth() * this->cabecalhoBitMap.GetBiWidth();
    for (int i = 0; i < this->cabecalhoBitMap.GetBiHeigth(); i++) {
        for (int j = 0; j < this->cabecalhoBitMap.GetBiWidth(); j++) {
            somaR += (int) (this->matrizPixels[i][j].GetR());
            somaG += (int) (this->matrizPixels[i][j].GetG());
            somaB += (int) (this->matrizPixels[i][j].GetB());
        }
    }
    double *valores;
    valores = new double[3];
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
            //grava o header
            arquivoSaida.write((char*) this->cabecalhoImagem.GetBfType(),
                    sizeof (char) * 2);
            arquivoSaida.write((char*)  this->cabecalhoImagem.GetBfSize(),
                    sizeof (this->cabecalhoImagem.GetBfSize()));
            arquivoSaida.write((char*) this->cabecalhoImagem.GetBfReser1(),
                    sizeof (this->cabecalhoImagem.GetBfReser1()));
            arquivoSaida.write((char*) this->cabecalhoImagem.GetBfReser2(),
                    sizeof (this->cabecalhoImagem.GetBfReser2()));
            arquivoSaida.write((char*) this->cabecalhoImagem.GetBfOffSetBits(),
                    sizeof (this->cabecalhoImagem.GetBfOffSetBits()));

            //grava o cabeçalho da imagem
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiSize(),
                    sizeof (this->cabecalhoBitMap.GetBiSize()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiWidth(),
                    sizeof (this->cabecalhoBitMap.GetBiWidth()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiHeigth(),
                    sizeof (this->cabecalhoBitMap.GetBiHeigth()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiPlanes(),
                    sizeof (this->cabecalhoBitMap.GetBiPlanes()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiBitCount(),
                    sizeof (this->cabecalhoBitMap.GetBiBitCount()));

            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiCompress(),
                    sizeof (this->cabecalhoBitMap.GetBiCompress()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiSizeImage(),
                    sizeof (this->cabecalhoBitMap.GetBiSizeImage()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiXPPMeter(),
                    sizeof (this->cabecalhoBitMap.GetBiXPPMeter()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiYPPMeter(),
                    sizeof (this->cabecalhoBitMap.GetBiYPPMeter()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiCrlUsed(),
                    sizeof (this->cabecalhoBitMap.GetBiCrlUsed()));
            arquivoSaida.write((char*) this->cabecalhoBitMap.GetBiClrImport(),
                    sizeof (this->cabecalhoBitMap.GetBiClrImport()));


            //se tem paleta de cores grava a paleta e a matriz
            if (this->paletaCores != NULL) {
                unsigned char r, g, b, t;
                for (int i = 0; i < this->cabecalhoBitMap.GetBiCrlUsed(); i++) {
                    b = this->paletaCores[i].GetBlue();
                    g = this->paletaCores[i].GetGreen();
                    r = this->paletaCores[i].GetRed();
                    t = this->paletaCores[i].GetReservado();
                    arquivoSaida.write((char*) & b, sizeof (unsigned char));
                    arquivoSaida.write((char*) & g, sizeof (unsigned char));
                    arquivoSaida.write((char*) & r, sizeof (unsigned char));
                    arquivoSaida.write((char*) & t, sizeof (unsigned char));
                }

                //grava a matriz para 8 bits
                unsigned char elemento;
                int linha = 0, coluna = 0;
                while (true) {
                    try {
                        int indice = this->findIndex(this->matrizPixels[linha][coluna].GetR(),
                                this->matrizPixels[linha][coluna].GetG(),
                                this->matrizPixels[linha][coluna].GetB());
                        char* hex;
                        std::sprintf(hex, "%x", indice);
                        arquivoSaida.write(hex, sizeof (hex));
                        coluna++;
                        if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                            linha++;
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
                unsigned char r, g, b;
                int linha = 0, coluna = 0;
                while (true) {
                    arquivoSaida.write((char*) this->matrizPixels[linha][coluna].GetB(),
                            sizeof (unsigned char));
                    arquivoSaida.write((char*) this->matrizPixels[linha][coluna].GetG(),
                            sizeof (unsigned char));
                    arquivoSaida.write((char*) this->matrizPixels[linha][coluna].GetR(),
                            sizeof (unsigned char));

                    coluna++;
                    if (coluna == this->cabecalhoBitMap.GetBiWidth()) {
                        linha++;
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

int BMP::findIndex(unsigned char r, unsigned char g, unsigned char b) {
    for (int i = 0; i < this->cabecalhoBitMap.GetBiCrlUsed(); i++) {
        if ((r == this->paletaCores[i].GetRed())
                && (g == this->paletaCores[i].GetGreen())
                && (b == this->paletaCores[i].GetBlue())) {
            return i;
        }
    }
    return 0;
}


