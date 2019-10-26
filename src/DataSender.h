#ifndef DATASENDER_H
#define DATASENDER_H
#include <QString>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

struct LogData;

class DataSender : public QObject
{
    Q_OBJECT
public:
    DataSender();
    void send(const LogData& data);

signals:
    void finished();

private:
    QString _peerAddr;
    QNetworkAccessManager _networkMgr;
};

#endif // DATASENDER_H
