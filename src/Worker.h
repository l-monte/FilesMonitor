#ifndef WORKER_H
#define WORKER_H

#include "FilesReader/FileReader.h"
#include "ArchiveWriter/ArchiveWriter.h"
#include "MonitorDefs.h"
#include <QRunnable>
#include <QObject>
#include <functional>

class QString;

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Worker(const WorkerData& data);

    Worker(const Worker& o) = delete;
    Worker(Worker&& o) = delete;
    Worker& operator=(Worker&& o) = delete;
    Worker& operator=(const Worker& o) = delete;
    ~Worker() = default;

signals:
    void sendData(QString data);

protected:
    virtual void run();

    void sendLogPortionHandler(const QList<QString>& logs);

private:
    QString _filePath;
    QString _archivePath;
    QString _endpointAddr;

    FileReader _reader;
    ArchiveWriter _writer;

public:
    std::function<void(std::pair<QString, bool>)> _respHandler;
};

#endif // WORKER_H
