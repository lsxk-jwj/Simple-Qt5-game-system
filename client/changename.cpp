#include "changename.h"
#include "ui_changename.h"

ChangeName::ChangeName(QWidget *parent, std::string name) :
    QDialog(parent),
    ui(new Ui::ChangeName)
{
    ui->setupUi(this);
    ui->name->setPlaceholderText(QString::fromStdString(name));
    this->setWindowTitle(QString("Hello!!"));
}

const QString ChangeName::getName(){
    return ui->name->text();
}

ChangeName::~ChangeName()
{
    delete ui;
}
