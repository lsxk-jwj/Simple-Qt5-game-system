/********************************************************************************
** Form generated from reading UI file 'guessnum.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUESSNUM_H
#define UI_GUESSNUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuessNumClient
{
public:
    QLabel *label_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *magic_numbers;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *guess_numbers;
    QPushButton *submit;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *result;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *round;
    QFrame *line;
    QGroupBox *rivals_list;

    void setupUi(QWidget *GuessNumClient)
    {
        if (GuessNumClient->objectName().isEmpty())
            GuessNumClient->setObjectName(QStringLiteral("GuessNumClient"));
        GuessNumClient->resize(815, 761);
        label_5 = new QLabel(GuessNumClient);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 20, 811, 71));
        QFont font;
        font.setPointSize(40);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget = new QWidget(GuessNumClient);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 100, 714, 61));
        magic_numbers = new QHBoxLayout(horizontalLayoutWidget);
        magic_numbers->setObjectName(QStringLiteral("magic_numbers"));
        magic_numbers->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_2 = new QWidget(GuessNumClient);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(50, 190, 714, 78));
        guess_numbers = new QHBoxLayout(horizontalLayoutWidget_2);
        guess_numbers->setObjectName(QStringLiteral("guess_numbers"));
        guess_numbers->setContentsMargins(0, 0, 0, 0);
        submit = new QPushButton(GuessNumClient);
        submit->setObjectName(QStringLiteral("submit"));
        submit->setGeometry(QRect(340, 290, 131, 51));
        QFont font1;
        font1.setPointSize(20);
        submit->setFont(font1);
        horizontalLayoutWidget_3 = new QWidget(GuessNumClient);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(250, 370, 281, 80));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        horizontalLayout_3->addWidget(label_6);

        result = new QLabel(horizontalLayoutWidget_3);
        result->setObjectName(QStringLiteral("result"));
        QFont font2;
        font2.setPointSize(30);
        result->setFont(font2);
        result->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(result);

        horizontalLayoutWidget_4 = new QWidget(GuessNumClient);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(250, 450, 281, 80));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(horizontalLayoutWidget_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font1);

        horizontalLayout_4->addWidget(label_11);

        round = new QLabel(horizontalLayoutWidget_4);
        round->setObjectName(QStringLiteral("round"));
        round->setFont(font2);

        horizontalLayout_4->addWidget(round);

        line = new QFrame(GuessNumClient);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 560, 821, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        rivals_list = new QGroupBox(GuessNumClient);
        rivals_list->setObjectName(QStringLiteral("rivals_list"));
        rivals_list->setGeometry(QRect(30, 590, 751, 151));
        rivals_list->setFont(font1);

        retranslateUi(GuessNumClient);

        QMetaObject::connectSlotsByName(GuessNumClient);
    } // setupUi

    void retranslateUi(QWidget *GuessNumClient)
    {
        GuessNumClient->setWindowTitle(QApplication::translate("GuessNumClient", "Guess Number Game", 0));
        label_5->setText(QApplication::translate("GuessNumClient", "The Magic Number", 0));
        submit->setText(QApplication::translate("GuessNumClient", "Submit", 0));
        label_6->setText(QApplication::translate("GuessNumClient", "Result:", 0));
        result->setText(QApplication::translate("GuessNumClient", "None", 0));
        label_11->setText(QApplication::translate("GuessNumClient", "Round:", 0));
        round->setText(QApplication::translate("GuessNumClient", "0", 0));
        rivals_list->setTitle(QApplication::translate("GuessNumClient", "Rivals:", 0));
    } // retranslateUi

};

namespace Ui {
    class GuessNumClient: public Ui_GuessNumClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESSNUM_H
