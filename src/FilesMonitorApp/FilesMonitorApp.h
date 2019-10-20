#ifndef FILESMONITORAPP_H
#define FILESMONITORAPP_H
#include <QFileInfo>
#include <QObject>
#include <QThread>
#include "../MonitorDefs.h"
#include "../FileScanner.h"

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
    void onResultReady(const QString& file);

private:
    void setupOneThread(const QString& file);

private:
    QFileInfo _rootDir;
    QFileInfo _archDir;

    Worker* _worker;
    QThread _thread;

    FileNameToWasChangedMap _filesMap;
    FileScanner _fileScanner;
};

#endif // FILESMONITORAPP_H
