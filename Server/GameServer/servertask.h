#ifndef SERVERTASK_H
#define SERVERTASK_H

#include <QObject>
#include <QRunnable>

class ServerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ServerTask();

signals:
    void result(int number);

protected:
    void run() override;
};

#endif // SERVERTASK_H
