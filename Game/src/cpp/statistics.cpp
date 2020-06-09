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
    data.platform = tap::_linux;
    client->sendToServer(&data, sizeof(data));
}

Statistics::~Statistics()
{
    delete client;
}
