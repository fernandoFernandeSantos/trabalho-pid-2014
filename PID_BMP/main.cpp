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
ifstream inputOperacao;
bool imagemAberta = false;
bool imagem2Aberta = false;

static void continua() {
    cout << "Precione [ENTER] para continuar\n";
    getchar();
    getchar();
}

static void histogramOperations(BMP& arquivo) {
    if (!input.is_open() || !imagemAberta) {
        cout << "Primeiro abra o arquivo\n";
        return;
    }
    ushort opcao = 1;
    bool histograma = false;
    while (opcao) {
        system("clear");
        cout << "=> Operações com histograma\n" <<
                " ==> [1] Gerar histograma\n" <<
                " ==> [2] Equalizar histograma\n" <<
                " ==> [0] Voltar\n" <<
                "opção: ";
        cin >> opcao;
        char s = 'n';
        switch (opcao) {
            case 1:
            {
                if (arquivo.makeHistogram()) {
                    cout << "Histograma gerado com sucesso\n";
                    histograma = true;
                } else {
                    cout << "Erro na geração do histograma\n";
                    continua();
                    break;
                }
                cout << "Gerando visualização...\nA imagem é em escala de cinza[S/n]: ";
                cin >> s;
                if (s == 'S') {
                    arquivo.printHistogram(true);
                } else {
                    arquivo.printHistogram(false);
                }
                continua();
                break;
            }
            case 2:
            {
                if (!histograma) {
                    arquivo.makeHistogram();
                }
                if (arquivo.histogramEqualizer()) {
                    cout << "Histograma equalizado\n";
                } else {
                    cout << "Problemas na equalização\n";
                    continua();
                    break;
                }
                cout << "Gerando visualização...\nA imagem é em escala de cinza[S/n]: ";
                cin >> s;
                if (s == 'S') {
                    arquivo.makeHistogram();
                    arquivo.printHistogram(true);
                } else {
                    arquivo.makeHistogram();
                    arquivo.printHistogram(false);
                }
                continua();
                break;
            }
        }

    }
}

static void logicAndAritmetics(BMP& arquivo1, BMP& arquivo2) {
    if (!input.is_open() || !imagemAberta || !inputOperacao.is_open() || !imagem2Aberta) {
        cout << "Primeiro abra o arquivo\n";
        return;
    }
    ushort opcao = 1;
    char oper[3];
    while (opcao) {
        system("clear");
        cout << "=> Operações lógicas e aritméticas\n" <<
                " ==> [1] Lógicas AND, OR e NOT\n" <<
                " ==> [2] Aritméticas + e -\n" <<
                " ==> [0] Voltar\n" <<
                "opção: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
            {
                cout << "AND, OR ou NOT: ";
                cin >> oper;
                //1 = &; 2 = |, 3 = +, 4 = -, 5 = ~

                if (!strcmp(oper, "AND")) arquivo1.operations(arquivo2, 1);
                if (!strcmp(oper, "OR")) arquivo1.operations(arquivo2, 2);
                if (!strcmp(oper, "NOT")) arquivo1.operations(arquivo2, 5); // vai a 2, mas não faz nada
                break;
            }
            case 2:
            {
                cout << "MAIS ou MENOS:";
                cin >> oper;

                if (!strcmp(oper, "MAIS")) arquivo1.operations(arquivo2, 3);
                if (!strcmp(oper, "MENOS")) arquivo1.operations(arquivo2, 4);
                break;
            }
        }

    }
}

static void maskOperations(BMP& arquivo) {
    if (!input.is_open() || !imagemAberta) {
        cout << "Primeiro abra o arquivo\n";
        return;
    }
    ushort opcao = 1;
    while (opcao) {
        system("clear");
        cout << "=> Operações com máscaras\n" <<
                " ==> [1] Com máscara genérica\n" <<
                " ==> [2] Sobel\n" <<
                " ==> [3] Roberts\n" <<
                " ==> [4] Média\n" <<
                " ==> [5] Mediana\n" <<
                " ==> [0] Voltar\n" <<
                "opção: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
            {
                uint ordem = 0;
                cout << "Entre com a ordem da máscara: ";
                cin >> ordem;
                Matriz<double> mask(ordem, ordem);
                if (ordem <= 0) break;
                cout << "Entre com a matriz\n";
                cin >> mask;
                arquivo.convolucao(mask);
                cout << "Convolução terminada\n";
                continua();
                break;
            }
            case 2:
            {
                cout << "Filtro de Sobel...\n";
                arquivo.sobel();
                cout << "Filtro aplicado\n";
                continua();
                break;
            }
            case 3:
            {
                char pos;
                cout << "Filtro de roberts\n";
                cout << "Deseja Roberts Vertical[V] ou Horizontal[H]: ";
                cin >> pos;
                if (pos == 'V')
                    arquivo.roberts(true);
                else
                    arquivo.roberts(false);
                cout << "Filtro aplicado\n";
                continua();
                break;
            }
            case 4:
            {
                ushort ordem;
                cout << "Filtro da média\n";
                cout << "Digite a ordem da janela para o filtro da média: ";
                cin >> ordem;
                if (ordem > 0) {
                    arquivo.media(ordem);
                    cout << "Filtro aplicado\n";
                    continua();
                }
                break;
            }
            case 5:
            {
                ushort ordem;
                cout << "Filtro da mediana\n";
                cout << "Digite a ordem da janela para o filtro da mediana: ";
                cin >> ordem;
                if (ordem > 0) {
                    arquivo.mediana(ordem);
                    cout << "Filtro aplicado\n";
                    continua();
                }
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
            " [8]  - Operações lógicas e aritméticas\n" <<
            " [9]  - Operações com máscaras\n" <<
            " [10] - Limiarização da imagem\n" <<
            " [11] - Converter a imagem para níveis cinza\n" <<
            " [12] - Detecção de olhos\n" <<
            " [0]  - Sair\n\n" <<
            "Opção:";
}

int main() {
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
                cout << "Arquivo salvo com sucesso\n";
                continua();
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
                    cout << "Primeiro abra o arquivo\n";
                    continua();
                    break;
                }
                histogramOperations(arquivo);
                break;
            }
            case 8: //operações lógicas e aritméticas
            {
                if (!input.is_open()) {
                    cout << "Primeiro abra o primeiro arquivo\n";
                    continua();
                    break;
                }
                cout << "\nEntre com o nome do segundo arquivo(maxímo 100 caracteres) ";
                cout << "\n*Caso esteja no diretório do projeto: NomeImagem.bmp\n ";
                cout << "\n*Caso esteja fora do diretório do projeto: /MeuDiretorio/NomeImagem.bmp\n ";
                cout << "\nNome:";
                cin >> nome;
                try {
                    inputOperacao.open(nome, ios::binary);
                    if (!(inputOperacao.good() && inputOperacao.is_open())) {
                        cout << "Não foi possível abrir o arquivo " << nome << endl;
                        continua();
                        break;
                    }
                    BMP imagem2;
                    imagem2.read(&inputOperacao);
                    imagem2Aberta = true;
                    logicAndAritmetics(arquivo, imagem2);
                    continua();

                } catch (ifstream::failure e) {
                    cout << "Exception opening/reading/closing file\n";
                    cout << e.what() << endl;
                    break;
                }

                break;
            }
            case 9: //operações com máscaras
            {
                maskOperations(arquivo);
                break;
            }
            case 10:
            {
                if (!input.is_open()) {
                    cout << "Primeiro abra o arquivo\n";
                    continua();
                    break;
                }
                ushort limiar = 0;
                cout << "Digite um limiar para o processo de limiarização: ";
                cin >> limiar;
                arquivo.limiarImagem(limiar);
                cout << "Limiar aplicado\n";
                continua();
                break;
            }
            case 11:
            {
                if (!input.is_open()) {
                    cout << "Primeiro abra o arquivo\n";
                    continua();
                    break;
                }
                cout << "Conversão de imagem para tons de cinza\n";
                BMP novo(arquivo.imageToGray());
                cout << "\n Entre como nome do arquivo de saida: ";
                cin >> nome;
                try {
                    novo.salvar(nome);

                } catch (ifstream::failure e) {
                    cout << "Exception opening/reading/closing file\n";
                    cout << e.what() << endl;
                    continua();
                    break;
                }
                cout << "Arquivo salvo com sucesso\n";
                continua();
                break;
            }
            case 12:
            {
                if (!input.is_open()) {
                    cout << "Primeiro abra o arquivo\n";
                    continua();
                    break;
                }
                
                arquivo.houghTransformation(20, 100);
                cout << "Hough aplicado\n";
                continua();
                break;
            }
            case 0:
            {
                if (input.is_open())
                    input.close();
                break;
            }


        }
        opcoes();
        scanf("%hu", &opcao);
    }
    system("clear");
    input.close();


    return 0;
}

