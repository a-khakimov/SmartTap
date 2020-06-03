#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include "tcpclient.h"

class Statistics : public QObject
{
    Q_OBJECT
public:
    Statistics(QObject* parent = nullptr);
    virtual ~Statistics();

private:
    TcpClient* client;

private slots:
    void send();
};

#endif // STATISTICS_H
