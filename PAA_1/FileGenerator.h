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

using namespace std;

class FileGenerator {
public:

    FileGenerator(){}
    virtual ~FileGenerator(){}

    int generate(string pasta) {
        string pastaSaida = "cd " + pasta;
        if (system(pastaSaida.c_str())) {
            cout << "Criando pasta\n";
            string foi = "mkdir " + pasta;
            system(foi.c_str());
            //pasta = "cd " + pasta;
            //system(pasta.c_str());
        }

        ofstream output;
        ostringstream outputstring;
        srand((unsigned) time(0));
        //randomico
        for (int j = 1; j <= 6; j++) {

            int limit = 10000;

            while (limit <= 100000) {
                outputstring << pasta + "/arq" << limit << "n" << j << ".txt";
                string s = outputstring.str();
                cout << s << endl;
                output.open(s.c_str());
                outputstring.str("");
                outputstring.clear();


                for (int i = 0; i < limit; i++) {
                    output << rand() << endl;
                }
                output.close();

                limit += 5000;
            } //fim while limit

        } //fim for randomico
        outputstring.str("");
        outputstring.clear();

        //sequencial
        for (int i = 1; i <= 2; i++) {
            int limit = 10000;
            while (limit <= 100000) {

                //int vetor[limit];

                outputstring << pasta + "/arq" << limit << "seq" << "n" << i << ".txt";

                string s = outputstring.str();
                cout << s << endl;
                output.open(s.c_str());
                outputstring.str("");
                outputstring.clear();

                for (int j = 0; j < limit; j++) {
                    output << j << endl;
                }
                limit += 5000;

                output.close();
            }
        }

        //inverso - pior caso
        outputstring.str("");
        outputstring.clear();

        for (int i = 1; i <= 2; i++) {

            int limit = 10000;
            while (limit <= 100000) {

                //int vetor[limit];

                outputstring << pasta + "/arq" << limit << "inv" << "n" << i << ".txt";

                string s = outputstring.str();
                cout << s << endl;
                output.open(s.c_str());
                outputstring.str("");
                outputstring.clear();
                //salva invertido
                for (int j = limit - 1; j >= 0; j--)
                    output << j << endl;


                limit += 5000;
                output.close();
            }
        }
    }
private:
    
};

#endif	/* FILEGENERATOR_H */

