#include "DataSender.h"
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include "../MonitorConfig.h"
DataSender::DataSender() : _peerAddr(PEER_ADDR), _networkMgr()
{

}

void DataSender::send(const QList<QString>& data)
{
    QUrl serviceUrl = QUrl(_peerAddr);
    QNetworkRequest request(serviceUrl);
    QJsonObject json;                   // TODO add proper message format
    json.insert("data", data.first());
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));
    QNetworkReply *reply = _networkMgr.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &DataSender::finished);
}
