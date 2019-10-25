#ifndef WORKER_H
#define WORKER_H

#include "FilesReader/FileReader.h"
#include "ArchiveWriter/ArchiveWriter.h"
#include "MonitorDefs.h"
#include <QRunnable>
#include <QObject>
#include <functional>

class QString;
class FilesMonitorApp;

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

protected:
    virtual void run();

private:
    QFile _logFile;
    QFile _archiveFile;
};

#endif // WORKER_H
