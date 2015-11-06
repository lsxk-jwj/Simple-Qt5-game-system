#include "mainwindow.h"
#include "request.h"
#include <QApplication>
#include <QDebug>


Request request;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qDebug() << "Starting main window...\n";
    w.show();

    return a.exec();
}
