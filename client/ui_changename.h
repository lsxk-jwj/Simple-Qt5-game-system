/********************************************************************************
** Form generated from reading UI file 'changename.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGENAME_H
#define UI_CHANGENAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ChangeName
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *name;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *ChangeName)
    {
        if (ChangeName->objectName().isEmpty())
            ChangeName->setObjectName(QStringLiteral("ChangeName"));
        ChangeName->resize(323, 291);
        buttonBox = new QDialogButtonBox(ChangeName);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(220, 180, 81, 91));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        name = new QLineEdit(ChangeName);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(20, 190, 181, 41));
        QFont font;
        font.setPointSize(15);
        name->setFont(font);
        label = new QLabel(ChangeName);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, -10, 291, 121));
        QFont font1;
        font1.setPointSize(40);
        label->setFont(font1);
        label_2 = new QLabel(ChangeName);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 120, 261, 31));
        QFont font2;
        font2.setPointSize(16);
        label_2->setFont(font2);

        retranslateUi(ChangeName);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChangeName, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChangeName, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChangeName);
    } // setupUi

    void retranslateUi(QDialog *ChangeName)
    {
        ChangeName->setWindowTitle(QApplication::translate("ChangeName", "Change your name", 0));
        name->setText(QString());
        label->setText(QApplication::translate("ChangeName", "Welcome!", 0));
        label_2->setText(QApplication::translate("ChangeName", "Please fill out your name", 0));
    } // retranslateUi

};

namespace Ui {
    class ChangeName: public Ui_ChangeName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGENAME_H
