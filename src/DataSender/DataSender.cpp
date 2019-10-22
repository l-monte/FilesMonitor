#include "DataSender.h"
#include <QDebug>           //TODO: refactor
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>
DataSender::DataSender() : _ipAddr("https://monte.free.beeceptor.com"), _port(4200), _networkMgr()
{

}

void DataSender::send(const QList<QString>& data)
{
    qDebug() << "\tINFO: [DataSender::send] sending data to endpoint: " << data;

    QUrl serviceUrl = QUrl(_ipAddr);
    QNetworkRequest request(serviceUrl);
    QJsonObject json;
    json.insert("userid","xxxx");
    json.insert("userpass","xxxx");
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));
//    connect(&_networkMgr, &QNetworkAccessManager::finished,
//            this, [this](QNetworkReply *reply){ qDebug() << "\t [DataSender] received a response!!"; });
    _networkMgr.post(request, jsonData);
}

// https://monte.free.beeceptor.com
