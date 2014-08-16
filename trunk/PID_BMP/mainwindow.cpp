#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BMP.h"
#include <QFileDialog>
#include <QMessageBox>

QString fileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());
    /*
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

    }*/
}

void MainWindow::on_pushButton_clicked()
{
    BMP arquivo; //arquivo de entrada
    BMP novo;
    ifstream input, input2;
    std::string aux = fileName.toStdString();
    input.open(aux.c_str(), ios::binary);
    //input2.open("../Imagens/CanMan.bmp", ios::binary);

    /*
    if (!(input.good() && input.is_open())) {
        return;
    }
    //if (!(input2.good() && input2.is_open())) {
     //   return;
    //}
    try{
        arquivo.read(&input);
        //novo.read(&input2);
        cout << "antes\n";
                arquivo.printCabecalhoArquivo();
                arquivo.printCabecalhoImagem();
     //   arquivo.imageToGray("teste.bmp");
      //  arquivo.salvar("testeSalvo.bmp");
        arquivo.histogramEqualizer();
        arquivo.salvar("teste.bmp");
        cout << "\nDepoi\n";

        input.close();
        //input2.close();
    }catch(ifstream::failure e){
        cout << "Exception opening/reading/closing file\n";
        cout << e.what() << endl;
    }*/
    //return;
}
