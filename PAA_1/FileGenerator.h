/* 
 * File:   FileGenerator.h
 * Author: familia
 *
 * Created on 10 de Agosto de 2014, 16:29
 */

#ifndef FILEGENERATOR_H
#define	FILEGENERATOR_H
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

class FileGenerator {
public:
    
    FileGenerator();
    FileGenerator(const FileGenerator& orig);
    virtual ~FileGenerator();
    int generate(std::string pasta);

    
private:
    
    
    void worst_for_selection(int valor[], int tamanho);
    void sort(int valor[], int esquerda, int direita);
    void inverte(int v[], int fim);
    

};

#endif	/* FILEGENERATOR_H */

