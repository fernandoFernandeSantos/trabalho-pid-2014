#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BMP.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
bool salvo = true;
QString fileName;
BMP arquivo; //arquivo de entrada
ifstream input;


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
    std::string aux = fileName.toStdString();
    input.open(aux.c_str(), ios::binary);

    if (!(input.good() && input.is_open())) {
        QMessageBox msgBox;
        msgBox.setText("A imagem não pode ser aberta");
        msgBox.exec();
        return;
    }
    salvo = false;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_actionSair_triggered()
{
    if(!salvo){
        QMessageBox msgBox;
        msgBox.setText("A imagem foi modificada.");
        msgBox.setInformativeText("Deseja salvar?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
        {
            bool ok;
            QString text = QInputDialog::getText(this, tr("Salvar arquivo"),
                                                 tr("Nome de saida:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty()){
                std::string aux = text.toStdString();
                arquivo.salvar(aux.c_str());
            }
            break;
        }
        case QMessageBox::Cancel:
            exit(1);
            break;
        }

    }
}
