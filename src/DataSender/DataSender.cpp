#include "DataSender.h"
#include <QDebug>           //TODO: refactor
DataSender::DataSender() : _ipAddr(""), _port(4200)
{

}

void DataSender::send()
{
    qDebug() << "REST Data Sender: sending data...";
}

