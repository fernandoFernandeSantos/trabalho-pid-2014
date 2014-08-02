#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BMP.h"
#include <QFileDialog>
#include <QMessageBox>

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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

    }
}

void MainWindow::on_pushButton_clicked()
{
    BMP arquivo; //arquivo de entrada
    BMP novo;
    ifstream input, input2;
    input.open("/home/familia/NetBeansProjects/trunk/PID_BMP/Imagens/Flores.bmp", ios::binary);
    //input2.open("../Imagens/CanMan.bmp", ios::binary);

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
        arquivo.imageToGray();
        arquivo.salvar("teste.bmp");
        cout << "\nDepoi\n";
        arquivo.printCabecalhoArquivo();
        arquivo.printCabecalhoImagem();
        input.close();
        //input2.close();
    }catch(ifstream::failure e){
        cout << "Exception opening/reading/closing file\n";
        cout << e.what() << endl;
    }
    return;
}
