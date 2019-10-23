#include "GlobalDataSender.h"

#include <QDebug>           //TODO: refactor
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>

GlobalDataSender* GlobalDataSender::_instance = nullptr;

GlobalDataSender::GlobalDataSender()
{
}

GlobalDataSender* GlobalDataSender::instance()
{
    if (_instance == nullptr)
        _instance = new GlobalDataSender;

    return _instance;
}

void GlobalDataSender::send(QString data)
{
    qDebug() << "\t[GlobalDataSender::send] start of function\n";
    QUrl serviceUrl = QUrl("http://monte.free.beeceptor.com/test1/testFile");
    QNetworkRequest request(serviceUrl);
    QJsonObject json;
    json.insert("data",data);
    json.insert("userpass","xxxx");
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

//    connect(&_networkMgr, &QNetworkAccessManager::finished,
//            this, [this](QNetworkReply *reply){ qDebug() << "\t [DataSender] received a response!!"; });
    networkManager.post(request, jsonData);
}
