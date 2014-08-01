/* 
 * File:   header.h
 * Author: marcelo-note
 *
 * Created on 8 de Abril de 2014, 13:58
 */

#ifndef HEADER_H
#define	HEADER_H

#include <fstream>
#include <iostream>
#include <cstring> 

class Header {
private:
    unsigned char* BfType; //Assinatura do arquivo
    unsigned int BfSize; //Tamanho do arquivo em bytes
    unsigned short BfReser1; //Campo reservado, deve ser 0
    unsigned short BfReser2; //Campo reservado, deve ser 0
    unsigned int BfOffSetBits; //Deslocamento, em bytes,para o inicio da area de dados 
    //se usa paleta, então 14+40+(4 x NumeroDeCores), senão, 54
public:
    Header();
    Header(const Header & orig);
    ~Header();
    unsigned int GetBfOffSetBits() const;
    unsigned short GetBfReser1() const;
    unsigned short GetBfReser2() const;
    unsigned int GetBfSize() const;
//    unsigned short GetBfType() const;
    void SetBfOffSetBits(unsigned int BfOffSetBits);
    void SetBfReser1(unsigned short BfReser1);
    void SetBfReser2(unsigned short BfReser2);
    void SetBfSize(unsigned int BfSize);
//    void SetBfType(unsigned short BfType);
    
    unsigned char* GetBfType() ;
    void SetBfType(unsigned char* BfType);
    Header operator =(const Header &orig);

    void read(std::ifstream *input);
    void print();

};

#endif	/* HEADER_H */

