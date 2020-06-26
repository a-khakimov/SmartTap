#include "statistics.h"
#include "data.h"
#include <QDebug>

Statistics::Statistics(QObject *parent)
    : QObject { parent },
      client { new TcpClient(this, "localhost", 4040) }
{
    connect(client, &TcpClient::connected, this, &Statistics::send);
}

void Statistics::send()
{
    tap::RequestHeader data;
    data.id = tap::StatisticsDataId;
    data.platform = tap::_linux;
    client->sendToServer(&data, sizeof(data));
}

Statistics::~Statistics()
{
    delete client;
}
