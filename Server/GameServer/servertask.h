#ifndef SERVERTASK_H
#define SERVERTASK_H

#include <QObject>
#include <QRunnable>
#include <QHostAddress>
#include "data.h"

class ServerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ServerTask();
    explicit ServerTask(const QHostAddress clientAddr, const tap::StatisticsData data, QObject* parent = nullptr);
    virtual ~ServerTask();

signals:
    void result(int number);

protected:
    void run() override;

private:
    tap::StatisticsData m_data;
    QHostAddress m_clientAddr;
};

#endif // SERVERTASK_H
