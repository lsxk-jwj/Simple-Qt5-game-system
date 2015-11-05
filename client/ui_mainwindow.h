/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *board;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *name;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLabel *money;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QPushButton *BlackJackButton;
    QPushButton *GuessNumButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *serverIPDisplay;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *serverPortDisplay;
    QLabel *connectionStatus;
    QPushButton *TryConnectionButton;
    QPushButton *ConfigureServerButton;
    QPushButton *ChangeNameButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(553, 496);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 60, 380, 410));
        board = new QVBoxLayout(layoutWidget);
        board->setSpacing(6);
        board->setContentsMargins(11, 11, 11, 11);
        board->setObjectName(QStringLiteral("board"));
        board->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setPointSize(40);
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        name = new QLabel(layoutWidget);
        name->setObjectName(QStringLiteral("name"));
        QFont font1;
        font1.setFamily(QStringLiteral("WenQuanYi Zen Hei"));
        font1.setPointSize(40);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(7);
        name->setFont(font1);
        name->setStyleSheet(QStringLiteral("font: 63 40pt \"WenQuanYi Zen Hei\";"));

        horizontalLayout_4->addWidget(name);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font2;
        font2.setPointSize(20);
        label_5->setFont(font2);

        horizontalLayout->addWidget(label_5);

        money = new QLabel(layoutWidget);
        money->setObjectName(QStringLiteral("money"));
        QFont font3;
        font3.setPointSize(25);
        money->setFont(font3);

        horizontalLayout->addWidget(money);


        verticalLayout->addLayout(horizontalLayout);


        board->addLayout(verticalLayout);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        board->addItem(verticalSpacer_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        board->addItem(verticalSpacer_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        board->addItem(verticalSpacer_3);

        BlackJackButton = new QPushButton(layoutWidget);
        BlackJackButton->setObjectName(QStringLiteral("BlackJackButton"));
        BlackJackButton->setMinimumSize(QSize(0, 27));

        board->addWidget(BlackJackButton);

        GuessNumButton = new QPushButton(layoutWidget);
        GuessNumButton->setObjectName(QStringLiteral("GuessNumButton"));
        GuessNumButton->setMinimumSize(QSize(0, 27));
        GuessNumButton->setStyleSheet(QStringLiteral(""));

        board->addWidget(GuessNumButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        board->addItem(verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        board->addItem(verticalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font: 63 16pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label, 0, Qt::AlignRight);

        serverIPDisplay = new QLabel(layoutWidget);
        serverIPDisplay->setObjectName(QStringLiteral("serverIPDisplay"));
        serverIPDisplay->setStyleSheet(QLatin1String("font: 63 bold 16pt \"Ubuntu\";\n"
"color: rgb(255, 170, 0)"));

        horizontalLayout_2->addWidget(serverIPDisplay);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font: 63 16pt \"Ubuntu\";"));

        horizontalLayout_3->addWidget(label_3, 0, Qt::AlignRight);

        serverPortDisplay = new QLabel(layoutWidget);
        serverPortDisplay->setObjectName(QStringLiteral("serverPortDisplay"));
        serverPortDisplay->setStyleSheet(QLatin1String("font: 63 bold 16pt \"Ubuntu\";\n"
"color: rgb(12, 44, 255)"));

        horizontalLayout_3->addWidget(serverPortDisplay);


        verticalLayout_2->addLayout(horizontalLayout_3);


        board->addLayout(verticalLayout_2);

        connectionStatus = new QLabel(layoutWidget);
        connectionStatus->setObjectName(QStringLiteral("connectionStatus"));
        connectionStatus->setAlignment(Qt::AlignCenter);

        board->addWidget(connectionStatus);

        TryConnectionButton = new QPushButton(layoutWidget);
        TryConnectionButton->setObjectName(QStringLiteral("TryConnectionButton"));

        board->addWidget(TryConnectionButton);

        ConfigureServerButton = new QPushButton(layoutWidget);
        ConfigureServerButton->setObjectName(QStringLiteral("ConfigureServerButton"));

        board->addWidget(ConfigureServerButton);

        ChangeNameButton = new QPushButton(layoutWidget);
        ChangeNameButton->setObjectName(QStringLiteral("ChangeNameButton"));

        board->addWidget(ChangeNameButton);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Game Board", 0));
        label_2->setText(QApplication::translate("MainWindow", "Hi!", 0));
        name->setText(QApplication::translate("MainWindow", "Anomynous", 0));
        label_5->setText(QApplication::translate("MainWindow", "Money You Have:", 0));
        money->setText(QApplication::translate("MainWindow", "0", 0));
        BlackJackButton->setText(QApplication::translate("MainWindow", "BlackJack", 0));
        GuessNumButton->setText(QApplication::translate("MainWindow", "Guess Number", 0));
        label->setText(QApplication::translate("MainWindow", "Server IP:   ", 0));
        serverIPDisplay->setText(QApplication::translate("MainWindow", "127.0.1.1", 0));
        label_3->setText(QApplication::translate("MainWindow", "Server port:   ", 0));
        serverPortDisplay->setText(QApplication::translate("MainWindow", "8000", 0));
        connectionStatus->setText(QString());
        TryConnectionButton->setText(QApplication::translate("MainWindow", "Connect", 0));
        ConfigureServerButton->setText(QApplication::translate("MainWindow", "Configure Server", 0));
        ChangeNameButton->setText(QApplication::translate("MainWindow", "Change My Name", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
