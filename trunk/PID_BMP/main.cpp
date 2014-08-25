/* 
 * File:   main.cpp
 * Author: marcelo-note
 *
 * Created on 8 de Abril de 2014, 13:35
 */

#include"BMP.h"
#include <stdlib.h>
using namespace std;
ifstream input;
bool imagemAberta = false;

static void continua() {
    cout << "Precione [ENTER] para continuar\n";
    getchar();
    getchar();
}

static void histogramOperations(BMP arquivo){
    if(!input.is_open() || !imagemAberta){
        cout << "Primeiro abra o arquivo\n";
        return;
    }
    ushort opcao = 1;
    bool histograma = false;
    while(opcao){
        system("clear");
        cout << "=> Operações com histograma\n" <<
                " ==> [1] Gerar histograma\n" <<
                " ==> [2] Equalizar histograma\n" <<
                " ==> [3] Mostrar histograma (precisa do shotwell instalado)\n"<<
                " ==> [0] Voltar\n" <<
                "opção: ";
        cin >> opcao;
        char s = 'n';
        switch (opcao) {
            case 1:
            {
                if(arquivo.makeHistogram()){
                    cout << "Histograma gerado com sucesso\n";
                    histograma = true;
                }else{
                    cout << "Erro na geração do histograma\n";
                    continua();
                    break;
                }
                cout << "Gerando visualização...\nA imagem é em escala de cinza[S/n]: ";
                cin >> s;
                if(s == 'S'){
                    arquivo.printHistogram(true);
                }else{
                    arquivo.printHistogram(false);
                }
                continua();
                break;
            }
            case 2:
            {
                if(!histograma){
                    arquivo.makeHistogram();
                }
                if(arquivo.histogramEqualizer()){
                    cout << "Histograma equalizado\n";
                }else{
                    cout << "Problemas na equalização\n";
                    continua();
                    break;
                }
                cout << "Gerando visualização...\nA imagem é em escala de cinza[S/n]: ";
                cin >> s;
                if(s == 'S'){
                    arquivo.makeHistogram();
                    arquivo.printHistogram(true);
                }else{
                    arquivo.makeHistogram();
                    arquivo.printHistogram(false);
                }
                continua();
                break;
            }
        }

    }
}


static void opcoes() {
    system("clear");
    cout << "\n************************************************\n" <<
            "*                Trabalho de PID               *\n" <<
            "*                by Japa and Bordoada          *\n" <<
            "************************************************\n\n";
    cout << " [1]  - Abrir arquivo\n" <<
            " [2]  - Salvar arquivo\n" <<
            " [3]  - Mostrar cabeçalho do arquivo\n" <<
            " [4]  - Mostrar cabeçalho da imagem\n" <<
            " [5]  - Calcular valor médio dos pixels\n" <<
            " [6]  - Calcular variância\n" <<
            " [7]  - Operações com histograma\n" <<
            " [8]  - Converter a imagem para níveis cinza\n" <<
            " [9]  - Operações com máscaras\n" <<
            " [10] - Operações lógicas e aritiméticas\n" <<
            " [11] - Limiarização da imagem\n" <<
            " [0]  - Sair\n\n" <<
            "Opção:";
}


int main(void) {
    BMP arquivo; //arquivo de entrada
    unsigned short opcao;
    char nome[100];
    opcoes();
    scanf("%hu", &opcao);
    while (opcao) {
        switch (opcao) {
        case 1: //abrir o arquivo
        {
            char s = 'S';
            if (input.is_open()) {
                cout << "Já existe um arquivo aberto, deseja abrir outro arquivo S/n : ";
                cin >> s;
            }
            if (s == 'n')
                break;
            else
                input.close();
            cout << "\nEntre com o nome do arquivo(maxímo 100 caracteres): ";
            cout << "\n*Caso esteja no diretório do projeto: NomeImagem.bmp\n ";
            cout << "\n*Caso esteja fora do diretório do projeto: /MeuDiretorio/NomeImagem.bmp\n ";
            cout << "\nNome:";
            cin >> nome;
            try {
                input.open(nome, ios::binary);
                if (!(input.good() && input.is_open())) {
                    cout << "Não foi possível abrir o arquivo " << nome << endl;
                    continua();
                    break;
                }
                arquivo.read(&input);
                imagemAberta = true;
            } catch (ifstream::failure e) {
                cout << "Exception opening/reading/closing file\n";
                cout << e.what() << endl;
                continua();
                break;
            }
            break;
        }
        case 2: //salvar arquivo
        {
            if (!input.is_open()) {
                cout << "Primeiro abra o arquivo desejado\n";
                continua();
                break;
            }

            cout << "\n Entre como nome do arquivo de saida: ";
            cin >> nome;
            try {
                arquivo.salvar(nome);

            } catch (ifstream::failure e) {
                cout << "Exception opening/reading/closing file\n";
                cout << e.what() << endl;
                continua();
                break;
            }
            break;
        }
        case 3: //mostrar cabeçalho do arquivo
        {
            if (!input.is_open()) {
                cout << "Primeiro abra o arquivo desejado\n";
                continua();
                break;
            }
            arquivo.printCabecalhoArquivo();
            continua();

            break;
        }
        case 4: //mostrar o cabeçalho da imagem
        {
            if (!input.is_open()) {
                cout << "Primeiro abra o arquivo desejado\n";
                continua();
                break;
            }
            arquivo.printCabecalhoImagem();

            continua();
            break;
        }
        case 5: //valor médio
        {
            if (!(input.good() && input.is_open())) {
                cout << "Primeiro abra o arquivo desejado\n";
                continua();
                break;
            }
            long double *media = arquivo.valorMedio();
            cout << "Valor médio do R = " << media[0] << endl;
            cout << "Valor médio do G = " << media[1] << endl;
            cout << "Valor médio do B = " << media[2] << endl;
            continua();
            break;
        }
        case 6: //variância
        {
            if (!input.is_open()) {
                cout << "Primeiro abra o arquivo desejado\n";
                continua();
                break;
            }
            long double *variancia = arquivo.variancia(arquivo.valorMedio());
            cout << "Valor da Variância de R = " << variancia[0] << endl;
            cout << "Valor da Variância de G = " << variancia[1] << endl;
            cout << "Valor da Variância de B = " << variancia[2] << endl;
            continua();
            break;
        }
        case 7: //operações com histograma
        {
            if (!input.is_open()) {
                cout << "Primeiro abra o primeiro arquivo\n";
                continua();
                break;
            }
            histogramOperations(arquivo);
            break;
        }
        case 8:
        {
            break;
        }
        case 9:
        {

            break;
        }
        case 10:
        {
            break;
        }
        case 11:
        {
            break;
        }
        case 0:
        {
            if(input.is_open())
                input.close();
            break;
        }
            

        }
        opcoes();
        scanf("%hu", &opcao);
    }

    input.close();


    return 0;
}

