#include "DataSender.h"
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtNetwork/QNetworkReply>
#include "MonitorConfig.h"
#include "MonitorDefs.h"

namespace
{
const QString FILES_PATH = "files/";
}

DataSender::DataSender() : _peerAddr(PEER_ADDR), _networkMgr()
{
}

void DataSender::send(const LogData& data)
{
    QUrl serviceUrl = QUrl(_peerAddr + FILES_PATH + data.fileName);
    QNetworkRequest request(serviceUrl);

    QJsonArray logData;
    QJsonObject jsonObject;
    for (auto& line : data.logData)
        logData.push_back(line);
    jsonObject.insert("Log data", logData);

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData= jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    QNetworkReply *reply = _networkMgr.post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, &DataSender::finished);
}
