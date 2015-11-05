#include "configureserverdialog.h"
#include "ui_configureserverdialog.h"

ConfigureServerDialog::ConfigureServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureServerDialog)
{
    ui->setupUi(this);
}

ConfigureServerDialog::~ConfigureServerDialog()
{
    delete ui;
}

void ConfigureServerDialog::on_ConfigureServerDialog_accepted()
{
    serverIP = ui->ServerIP->text();
    serverPort = ui->ServerPort->text();
}

QString ConfigureServerDialog::getServerIP(){
    return serverIP;
}

QString ConfigureServerDialog::getServerPort(){
    return serverPort;
}
