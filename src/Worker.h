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
    Worker(FilesMonitorApp* mainApp, const WorkerData& data);

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
    void sendDataToRESTendpoint(const QList<QString>& data);

private:
    QFile _logFile;
    QFile _archiveFile;

    FilesMonitorApp* _mainApp;

public:
    std::function<void(std::pair<QString, bool>)> _respHandler;
};

#endif // WORKER_H
