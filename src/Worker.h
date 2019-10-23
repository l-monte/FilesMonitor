#ifndef WORKER_H
#define WORKER_H

#include "FilesReader/FileReader.h"
#include "ArchiveWriter/ArchiveWriter.h"
#include "MonitorDefs.h"
#include <QRunnable>
#include <QObject>
#include <functional>

class QString;
class QNetworkAccessManager;

typedef QList<QString> StringList;
//qRegisterMetaType< StringList >( "StringList" );
Q_DECLARE_METATYPE(StringList);

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Worker(QNetworkAccessManager* networkMgr, const WorkerData& data);

    Worker(const Worker& o) = delete;
    Worker(Worker&& o) = delete;
    Worker& operator=(Worker&& o) = delete;
    Worker& operator=(const Worker& o) = delete;
    ~Worker() = default;

signals:
    void sendData(QString data);

protected:
    virtual void run();
    void write(const QList<QString>& line);
    void read();
    void sendDataToRESTendpoint();

    void sendLogPortionHandler(const QString& logs);

private:
    QFile _logFile;
    QFile _archiveFile;

    QNetworkAccessManager* _networkMgr;

public:
    std::function<void(std::pair<QString, bool>)> _respHandler;
};

#endif // WORKER_H
