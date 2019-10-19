#ifndef FILESMONITORAPP_H
#define FILESMONITORAPP_H
#include <QFileInfo>
#include <QObject>
#include "../MonitorDefs.h"
#include "../FileScanner.h"

class Worker;
class QThread;

class FilesMonitorApp : public QObject
{
    Q_OBJECT
public:
    FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory, QObject *parent = nullptr);
    virtual ~FilesMonitorApp();

private:
    QFileInfo _rootDir;
    QFileInfo _archDir;


    Worker* _worker;
//    QThread* _thread;       //TODO worker and thread

//    FileNameToWasChangedMap _filesMap;
    FileScanner _fileScanner;
};

#endif // FILESMONITORAPP_H
