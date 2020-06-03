#include "statistics.h"
#include "data.h"
#include <QDebug>

Statistics::Statistics(QObject *parent)
    : QObject { parent },
      client { new TcpClient(this, "localhost", 4040) }
{
    connect(client, SIGNAL(connected()), this, SLOT(send()));
}

void Statistics::send()
{
    tap::StatisticsData data;
    data.platform = tap::_linux + 2;
    client->sendToServer(&data, sizeof(data));
    qDebug() << "Send statistic";
}

Statistics::~Statistics()
{
    delete client;
}
