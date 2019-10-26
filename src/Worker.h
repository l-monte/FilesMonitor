#ifndef WORKER_H
#define WORKER_H

#include <QFile>
#include "MonitorDefs.h"
#include <QRunnable>
#include <QObject>

class QString;
class FilesMonitorApp;

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Worker(const WorkerSetupData& data);

    Worker(const Worker& o) = delete;
    Worker(Worker&& o) = delete;
    Worker& operator=(Worker&& o) = delete;
    Worker& operator=(const Worker& o) = delete;
    ~Worker() = default;

signals:
    void finished(const QString& fileName);

protected:
    virtual void run();

private:
    QString retrieveLogFileName() const;

    QFile _logFile;
    QFile _archiveFile;
};

#endif // WORKER_H
