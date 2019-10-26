#ifndef FILESMONITORAPP_H
#define FILESMONITORAPP_H
#include <QMap>
#include <QObject>
#include <QFileInfo>
#include <QThreadPool>
#include "MonitorDefs.h"
#include "FileScanner.h"

class Worker;

class FilesMonitorApp : public QObject
{
    Q_OBJECT
public:
    FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory, QObject *parent = nullptr);
    virtual ~FilesMonitorApp();


private slots:
    void onNewFileAdded(const QString& file);
    void onFileModified(const QString& file);
    void onFileRemoved(const QString& file);
    void onWorkerFinished(const QString& fileName);

private:
    QFileInfo _rootDir;
    QFileInfo _archDir;

    QThreadPool _threadPool;

    FileScanner _fileScanner;

    QMap<FileName, WorkerState> _fileToWorkerStateMap;
};

#endif // FILESMONITORAPP_H
