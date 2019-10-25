#ifndef DATASENDER_H
#define DATASENDER_H
#include <QString>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class DataSender : public QObject
{
    Q_OBJECT
public:
    DataSender();
    void send(const QList<QString>& data);

signals:
    void finished();

private:
    QString _peerAddr;
    QNetworkAccessManager _networkMgr;
};

#endif // DATASENDER_H
