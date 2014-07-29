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
    ifstream input;
    input.open("Imagens/Gaviao.bmp", ios::binary);
    if (!(input.good() && input.is_open())) {
        return;
    }
    cout << "Passou aqui \n";
    arquivo.read(&input);
    arquivo.makeHistogram();
    cout << arquivo.GetHistogram();

}