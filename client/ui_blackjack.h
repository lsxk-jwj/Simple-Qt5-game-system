/********************************************************************************
** Form generated from reading UI file 'blackjack.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLACKJACK_H
#define UI_BLACKJACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_BlackJackClient
{
public:

    void setupUi(QDialog *BlackJackClient)
    {
        if (BlackJackClient->objectName().isEmpty())
            BlackJackClient->setObjectName(QStringLiteral("BlackJackClient"));
        BlackJackClient->resize(320, 240);

        retranslateUi(BlackJackClient);

        QMetaObject::connectSlotsByName(BlackJackClient);
    } // setupUi

    void retranslateUi(QDialog *BlackJackClient)
    {
        BlackJackClient->setWindowTitle(QApplication::translate("BlackJackClient", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class BlackJackClient: public Ui_BlackJackClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLACKJACK_H
