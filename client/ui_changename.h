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
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ChangeName
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *name;

    void setupUi(QDialog *ChangeName)
    {
        if (ChangeName->objectName().isEmpty())
            ChangeName->setObjectName(QStringLiteral("ChangeName"));
        ChangeName->resize(320, 151);
        buttonBox = new QDialogButtonBox(ChangeName);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(220, 40, 81, 221));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        name = new QLineEdit(ChangeName);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(20, 50, 181, 41));
        QFont font;
        font.setPointSize(15);
        name->setFont(font);

        retranslateUi(ChangeName);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChangeName, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChangeName, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChangeName);
    } // setupUi

    void retranslateUi(QDialog *ChangeName)
    {
        ChangeName->setWindowTitle(QApplication::translate("ChangeName", "Dialog", 0));
        name->setText(QApplication::translate("ChangeName", "fff", 0));
    } // retranslateUi

};

namespace Ui {
    class ChangeName: public Ui_ChangeName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGENAME_H
