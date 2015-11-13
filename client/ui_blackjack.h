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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlackJackClient
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QFrame *line;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *dealButton;
    QPushButton *hitButton;
    QPushButton *standButton;
    QPushButton *splitButton;
    QFrame *line_2;
    QLabel *label_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *deck1;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *dealerCards;
    QLabel *label_3;
    QLabel *label_7;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *deck2;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *rivalCards;
    QLabel *label_8;
    QGroupBox *groupBox;
    QRadioButton *chooseDeck1;
    QRadioButton *chooseDeck2;
    QLabel *label_9;
    QLabel *RivalName;
    QLabel *deck1_status;
    QLabel *deck2_status;
    QLabel *rival_status;

    void setupUi(QDialog *BlackJackClient)
    {
        if (BlackJackClient->objectName().isEmpty())
            BlackJackClient->setObjectName(QStringLiteral("BlackJackClient"));
        BlackJackClient->resize(867, 953);
        label = new QLabel(BlackJackClient);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(320, -30, 271, 141));
        QFont font;
        font.setPointSize(40);
        label->setFont(font);
        label_2 = new QLabel(BlackJackClient);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 70, 291, 41));
        QFont font1;
        font1.setPointSize(25);
        label_2->setFont(font1);
        label_5 = new QLabel(BlackJackClient);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 260, 291, 41));
        label_5->setFont(font1);
        line = new QFrame(BlackJackClient);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(-40, 230, 1021, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(BlackJackClient);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 660, 291, 41));
        label_4->setFont(font1);
        horizontalLayoutWidget_3 = new QWidget(BlackJackClient);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(250, 640, 451, 80));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        dealButton = new QPushButton(horizontalLayoutWidget_3);
        dealButton->setObjectName(QStringLiteral("dealButton"));

        horizontalLayout_4->addWidget(dealButton);

        hitButton = new QPushButton(horizontalLayoutWidget_3);
        hitButton->setObjectName(QStringLiteral("hitButton"));

        horizontalLayout_4->addWidget(hitButton);

        standButton = new QPushButton(horizontalLayoutWidget_3);
        standButton->setObjectName(QStringLiteral("standButton"));

        horizontalLayout_4->addWidget(standButton);

        splitButton = new QPushButton(horizontalLayoutWidget_3);
        splitButton->setObjectName(QStringLiteral("splitButton"));

        horizontalLayout_4->addWidget(splitButton);

        line_2 = new QFrame(BlackJackClient);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(-50, 730, 1021, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(BlackJackClient);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 810, 291, 41));
        label_6->setFont(font1);
        horizontalLayoutWidget_2 = new QWidget(BlackJackClient);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 360, 791, 81));
        deck1 = new QHBoxLayout(horizontalLayoutWidget_2);
        deck1->setObjectName(QStringLiteral("deck1"));
        deck1->setSizeConstraint(QLayout::SetFixedSize);
        deck1->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_5 = new QWidget(BlackJackClient);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(40, 130, 791, 81));
        dealerCards = new QHBoxLayout(horizontalLayoutWidget_5);
        dealerCards->setObjectName(QStringLiteral("dealerCards"));
        dealerCards->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(BlackJackClient);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 320, 111, 21));
        QFont font2;
        font2.setPointSize(20);
        label_3->setFont(font2);
        label_7 = new QLabel(BlackJackClient);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 460, 111, 21));
        label_7->setFont(font2);
        horizontalLayoutWidget_6 = new QWidget(BlackJackClient);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(40, 500, 791, 81));
        deck2 = new QHBoxLayout(horizontalLayoutWidget_6);
        deck2->setObjectName(QStringLiteral("deck2"));
        deck2->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_7 = new QWidget(BlackJackClient);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(40, 860, 791, 81));
        rivalCards = new QHBoxLayout(horizontalLayoutWidget_7);
        rivalCards->setObjectName(QStringLiteral("rivalCards"));
        rivalCards->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(BlackJackClient);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 600, 191, 41));
        label_8->setFont(font1);
        groupBox = new QGroupBox(BlackJackClient);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(220, 610, 281, 41));
        chooseDeck1 = new QRadioButton(groupBox);
        chooseDeck1->setObjectName(QStringLiteral("chooseDeck1"));
        chooseDeck1->setGeometry(QRect(30, 0, 191, 22));
        QFont font3;
        font3.setPointSize(18);
        chooseDeck1->setFont(font3);
        chooseDeck2 = new QRadioButton(groupBox);
        chooseDeck2->setObjectName(QStringLiteral("chooseDeck2"));
        chooseDeck2->setGeometry(QRect(150, 0, 191, 22));
        chooseDeck2->setFont(font3);
        label_9 = new QLabel(BlackJackClient);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(40, 760, 291, 41));
        label_9->setFont(font1);
        RivalName = new QLabel(BlackJackClient);
        RivalName->setObjectName(QStringLiteral("RivalName"));
        RivalName->setGeometry(QRect(220, 760, 291, 41));
        RivalName->setFont(font1);
        RivalName->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0)"));
        deck1_status = new QLabel(BlackJackClient);
        deck1_status->setObjectName(QStringLiteral("deck1_status"));
        deck1_status->setGeometry(QRect(140, 300, 151, 51));
        deck1_status->setFont(font2);
        deck2_status = new QLabel(BlackJackClient);
        deck2_status->setObjectName(QStringLiteral("deck2_status"));
        deck2_status->setGeometry(QRect(140, 440, 151, 51));
        deck2_status->setFont(font2);
        rival_status = new QLabel(BlackJackClient);
        rival_status->setObjectName(QStringLiteral("rival_status"));
        rival_status->setGeometry(QRect(320, 800, 151, 51));
        rival_status->setFont(font2);

        retranslateUi(BlackJackClient);

        QMetaObject::connectSlotsByName(BlackJackClient);
    } // setupUi

    void retranslateUi(QDialog *BlackJackClient)
    {
        BlackJackClient->setWindowTitle(QApplication::translate("BlackJackClient", "Blackjack Game", 0));
        label->setText(QApplication::translate("BlackJackClient", "BlackJack", 0));
        label_2->setText(QApplication::translate("BlackJackClient", "Dealer's Card:", 0));
        label_5->setText(QApplication::translate("BlackJackClient", "Your Cards:", 0));
        label_4->setText(QApplication::translate("BlackJackClient", "Your Action:", 0));
        dealButton->setText(QApplication::translate("BlackJackClient", "Deal", 0));
        hitButton->setText(QApplication::translate("BlackJackClient", "Hit", 0));
        standButton->setText(QApplication::translate("BlackJackClient", "Stand", 0));
        splitButton->setText(QApplication::translate("BlackJackClient", "Split", 0));
        label_6->setText(QApplication::translate("BlackJackClient", "Your Rival's Card:", 0));
        label_3->setText(QApplication::translate("BlackJackClient", "Deck 1", 0));
        label_7->setText(QApplication::translate("BlackJackClient", "Deck 2", 0));
        label_8->setText(QApplication::translate("BlackJackClient", "Active Deck:", 0));
        groupBox->setTitle(QString());
        chooseDeck1->setText(QApplication::translate("BlackJackClient", "Deck 1", 0));
        chooseDeck2->setText(QApplication::translate("BlackJackClient", "Deck 2", 0));
        label_9->setText(QApplication::translate("BlackJackClient", "Your Rival:", 0));
        RivalName->setText(QString());
        deck1_status->setText(QString());
        deck2_status->setText(QString());
        rival_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BlackJackClient: public Ui_BlackJackClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLACKJACK_H
