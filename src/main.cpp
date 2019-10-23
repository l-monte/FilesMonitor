#include <QCoreApplication>
#include "FilesMonitorApp/FilesMonitorApp.h"
#include "MonitorConfig.h"
#include <QDebug>                               // TODO
#include <QDir>
#include <QThreadPool>
#include <QFileInfo>



#include <QDebug>           //TODO: refactor
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != ENTRY_PARAM_NUMBER)
    {
        qDebug() << "ERROR: The parameters number is wrong!";
        a.quit();

        return -1;
    }

    if ( (not QDir(argv[1]).exists()) or (not QDir(argv[2]).exists()) or
          (not QFileInfo(argv[1]).isDir()) or (not QFileInfo(argv[1]).isDir()) )
    {
        qDebug() << "ERROR: One of passed directories isn't exist.";
        a.quit();

        return -1;
    }

//    QUrl serviceUrl = QUrl("http://monte.free.beeceptor.com/test1/file1");
//    QNetworkRequest request(serviceUrl);
//    QJsonObject json;
//    json.insert("userid","xxxx");
//    json.insert("userpass","xxxx");
//    QJsonDocument jsonDoc(json);
//    QByteArray jsonData= jsonDoc.toJson();
//    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
//    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));
//    QNetworkAccessManager networkManager;
////    connect(&_networkMgr, &QNetworkAccessManager::finished,
////            this, [this](QNetworkReply *reply){ qDebug() << "\t [DataSender] received a response!!"; });
//    networkManager.post(request, jsonData);

    FilesMonitorApp app(argv[1], argv[2], &a);

    return a.exec();
}

