#ifndef CONFIGURESERVERDIALOG_H
#define CONFIGURESERVERDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigureServerDialog;
}

class ConfigureServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureServerDialog(QWidget *parent = 0);
    ~ConfigureServerDialog();
    QString getServerIP();
    QString getServerPort();

private slots:
    void on_ConfigureServerDialog_accepted();

private:
    Ui::ConfigureServerDialog *ui;
    QString serverIP, serverPort;
};

#endif // CONFIGURESERVERDIALOG_H
