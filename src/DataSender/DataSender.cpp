#include "DataSender.h"
#include <QDebug>           //TODO: refactor
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>
DataSender::DataSender() : _ipAddr("http://monte.free.beeceptor.com"), _port(4200), _networkMgr()
{

}

void DataSender::send(const QList<QString>& data)
{
    qDebug() << "\tINFO: [DataSender::send] sending data to endpoint: " << data;

    QUrl serviceUrl = QUrl(_ipAddr);
    QNetworkRequest request(serviceUrl);
    QJsonObject json;
    json.insert("data", data.first());
    json.insert("userpass","xxxx");
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));
    QNetworkReply *reply = _networkMgr.post(request, jsonData);
}

// https://monte.free.beeceptor.com
