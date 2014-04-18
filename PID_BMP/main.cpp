/* 
 * File:   main.cpp
 * Author: marcelo-note
 *
 * Created on 8 de Abril de 2014, 13:35
 */

#include <iostream>
#include <fstream>
#include "Header.h"
#include "BitMapHeader.h"
#include "BMP.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    const char* FILENAM = "Flores.bmp";
//    const char* FILENAM = "CanMan.bmp";
    cout << "asd";
   
    BMP arquivo;
    ifstream input(FILENAM, ios::binary);
    arquivo.read(&input);
    arquivo.printInfo();
    input.close();
    
    /*
    ifstream o(FILENAM,ios::binary);

    Header h;
    
    h.read(&o);
    h.print();
    
    cout << endl;
    
    BitMapHeader bmh;
    
    bmh.read(&o);
    bmh.print();
    
    o.close();*/
    //
//    short readNumber;
//    o.read((char*)&readNumber,sizeof(readNumber));
//    
//    cout << readNumber;
    
//    o.write((char*)&toStore,sizeof(toStore));
//    o.close();
//
//    int toRestore=0;
//    ifstream i(FILENAM,ios::binary);
//    i.read((char*)&toRestore,sizeof(i));
//
//    cout << toRestore << endl;
    
    return 0;
}

