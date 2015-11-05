/********************************************************************************
** Form generated from reading UI file 'configureserverdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURESERVERDIALOG_H
#define UI_CONFIGURESERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigureServerDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ServerIP;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *ServerPort;

    void setupUi(QDialog *ConfigureServerDialog)
    {
        if (ConfigureServerDialog->objectName().isEmpty())
            ConfigureServerDialog->setObjectName(QStringLiteral("ConfigureServerDialog"));
        ConfigureServerDialog->resize(320, 163);
        buttonBox = new QDialogButtonBox(ConfigureServerDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 120, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(ConfigureServerDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 20, 224, 89));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        ServerIP = new QLineEdit(widget);
        ServerIP->setObjectName(QStringLiteral("ServerIP"));

        horizontalLayout->addWidget(ServerIP);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        ServerPort = new QLineEdit(widget);
        ServerPort->setObjectName(QStringLiteral("ServerPort"));

        horizontalLayout_2->addWidget(ServerPort);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ConfigureServerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigureServerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigureServerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigureServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureServerDialog)
    {
        ConfigureServerDialog->setWindowTitle(QApplication::translate("ConfigureServerDialog", "Dialog", 0));
        label->setText(QApplication::translate("ConfigureServerDialog", "Server IP: ", 0));
        ServerIP->setText(QApplication::translate("ConfigureServerDialog", "127.0.1.1", 0));
        label_2->setText(QApplication::translate("ConfigureServerDialog", "Server port: ", 0));
        ServerPort->setText(QApplication::translate("ConfigureServerDialog", "1234", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigureServerDialog: public Ui_ConfigureServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURESERVERDIALOG_H
