#ifndef CHANGENAME_H
#define CHANGENAME_H

#include <string>
#include <QDialog>

namespace Ui {
class ChangeName;
}

class ChangeName : public QDialog
{
    Q_OBJECT

public:

    const QString getName();
    explicit ChangeName(QWidget *parent = 0, std::string name = "");
    ~ChangeName();

private:
    Ui::ChangeName *ui;
};

#endif // CHANGENAME_H
