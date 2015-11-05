#ifndef UPDATOR_H
#define UPDATOR_H

#include <QTimer>

class Updator : public QTimer
{
    Q_OBJECT
public:
    explicit Updator(QObject *parent = 0);

signals:

public slots:

};

#endif // UPDATOR_H
