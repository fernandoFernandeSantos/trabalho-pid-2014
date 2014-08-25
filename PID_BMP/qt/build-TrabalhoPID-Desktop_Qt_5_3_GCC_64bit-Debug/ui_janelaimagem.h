/********************************************************************************
** Form generated from reading UI file 'janelaimagem.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JANELAIMAGEM_H
#define UI_JANELAIMAGEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_JanelaImagem
{
public:

    void setupUi(QDialog *JanelaImagem)
    {
        if (JanelaImagem->objectName().isEmpty())
            JanelaImagem->setObjectName(QStringLiteral("JanelaImagem"));
        JanelaImagem->resize(400, 300);

        retranslateUi(JanelaImagem);

        QMetaObject::connectSlotsByName(JanelaImagem);
    } // setupUi

    void retranslateUi(QDialog *JanelaImagem)
    {
        JanelaImagem->setWindowTitle(QApplication::translate("JanelaImagem", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class JanelaImagem: public Ui_JanelaImagem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JANELAIMAGEM_H
