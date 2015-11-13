/********************************************************************************
** Form generated from reading UI file 'blackjackresultdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLACKJACKRESULTDIALOG_H
#define UI_BLACKJACKRESULTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlackjackResultDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *dealer_result;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLabel *rival_result;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_5;
    QLabel *bet_balance;

    void setupUi(QDialog *BlackjackResultDialog)
    {
        if (BlackjackResultDialog->objectName().isEmpty())
            BlackjackResultDialog->setObjectName(QStringLiteral("BlackjackResultDialog"));
        BlackjackResultDialog->resize(342, 382);
        buttonBox = new QDialogButtonBox(BlackjackResultDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-130, 330, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(BlackjackResultDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 30, 262, 266));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        verticalLayout->addWidget(label);

        dealer_result = new QLabel(verticalLayoutWidget);
        dealer_result->setObjectName(QStringLiteral("dealer_result"));
        QFont font1;
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setWeight(75);
        dealer_result->setFont(font1);
        dealer_result->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(dealer_result);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        rival_result = new QLabel(verticalLayoutWidget);
        rival_result->setObjectName(QStringLiteral("rival_result"));
        rival_result->setFont(font1);
        rival_result->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(rival_result);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        bet_balance = new QLabel(verticalLayoutWidget);
        bet_balance->setObjectName(QStringLiteral("bet_balance"));
        bet_balance->setFont(font1);
        bet_balance->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(bet_balance);


        retranslateUi(BlackjackResultDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BlackjackResultDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BlackjackResultDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BlackjackResultDialog);
    } // setupUi

    void retranslateUi(QDialog *BlackjackResultDialog)
    {
        BlackjackResultDialog->setWindowTitle(QApplication::translate("BlackjackResultDialog", "Blackjack Result", 0));
        label->setText(QApplication::translate("BlackjackResultDialog", "You vs. Dealer:", 0));
        dealer_result->setText(QApplication::translate("BlackjackResultDialog", "result", 0));
        label_2->setText(QApplication::translate("BlackjackResultDialog", "You vs. Your rival:", 0));
        rival_result->setText(QApplication::translate("BlackjackResultDialog", "result", 0));
        label_5->setText(QApplication::translate("BlackjackResultDialog", "Net balance:", 0));
        bet_balance->setText(QApplication::translate("BlackjackResultDialog", "result", 0));
    } // retranslateUi

};

namespace Ui {
    class BlackjackResultDialog: public Ui_BlackjackResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLACKJACKRESULTDIALOG_H
