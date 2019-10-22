#include "DataSender.h"
#include <QDebug>           //TODO: refactor
DataSender::DataSender() : _ipAddr(""), _port(4200)
{

}

void DataSender::send(const QList<QString>& data)
{
    qDebug() << "\tINFO: [DataSender::send] sending data to endpoint: " << data;
}

