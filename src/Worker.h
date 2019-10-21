#ifndef WORKER_H
#define WORKER_H

#include "FilesReader/FileReader.h"
#include "ArchiveWriter/ArchiveWriter.h"
#include "DataSender/DataSender.h"
#include "MonitorDefs.h"
#include <QRunnable>
#include <functional>

class QString;

class Worker : public QRunnable
{
public:
    Worker(const WorkerData& data);

    Worker(const Worker& o) = delete;
    Worker(Worker&& o) = delete;
    Worker& operator=(Worker&& o) = delete;
    Worker& operator=(const Worker& o) = delete;
    ~Worker() = default;

protected:
    virtual void run();

private:
    QString _filePath;
    QString _archivePath;
    QString _endpointAddr;

    FileReader _reader;
    ArchiveWriter _writer;
    DataSender _sender;

public:
    std::function<void(std::pair<QString, bool>)> _respHandler;
};

#endif // WORKER_H
