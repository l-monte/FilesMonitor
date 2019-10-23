#ifndef FILESMONITORAPP_H
#define FILESMONITORAPP_H
#include <QFileInfo>
#include <QObject>
#include <QThreadPool>
#include <QVector>
#include "../MonitorDefs.h"
#include "../FileScanner.h"
#include <QNetworkAccessManager>

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

private:
    void respHandler(std::pair<QString, bool> respMsg);
    void sendDataToEndpoint(const QString& data);

private:
    QFileInfo _rootDir;
    QFileInfo _archDir;

    QThreadPool _threadPool;

    FileScanner _fileScanner;
    QNetworkAccessManager _networkMgr;
};

#endif // FILESMONITORAPP_H
