#include "FileScanner.h"
#include "MonitorConfig.h"
#include <QDebug>       // TODO

FileScanner::FileScanner(const QString& dirPath, QObject *parent) : QObject(parent),
    _rootDirectory(dirPath),
    _fileScanningTimer(new QTimer(this)),
    _watcher(this)
{
    //_rootDirectory.setNameFilters(QStringList() << QString(SUPPORTED_FILE_FORMAT));

    _fileScanningTimer->setSingleShot(false);
    _fileScanningTimer->setInterval(SCANNING_TIMER_INTERVAL);
    _fileScanningTimer->start();

    connect(_fileScanningTimer, &QTimer::timeout, this, [this]{ /*TODO*/qDebug() << "sending scanner timeout..."; emit scannerTimeout(); });

    connect(&_watcher, &QFileSystemWatcher::directoryChanged, this, [this]{ /*qDebug() << "FileScanner: received directoryChanged() signal.";*/ scanFiles(); });
    connect(&_watcher, &QFileSystemWatcher::fileChanged, this, [&](const QString& name){ /*qDebug() << "fileChanged() : " << name*/; onFileChanged(name); });
    _watcher.addPath(dirPath);
}

void FileScanner::scanFiles()
{
    QStringList fileList = _rootDirectory.entryList(QDir::Files);

    if (fileList.empty())
    qDebug() << "fileList is empty!" << endl;

    for (int i = 0; i < fileList.size(); ++i)
    {
        if (isNewFile(fileList[i]))
        {
            _watcher.addPath(_rootDirectory.path() + "/" + fileList[i]);
            emit newFileAdded(fileList[i]);
        }
    }
}

void FileScanner::onFileChanged(const QString& fileName)
{
    if (QFileInfo::exists(fileName))
    {
        emit fileModified(fileName);
    }
    else
    {
        _watcher.removePath(fileName);
        emit fileRemoved(fileName);
    }
}

bool FileScanner::isNewFile(const QString& fileName) const
{
    return (not _watcher.files().contains(_rootDirectory.path() + "/" + fileName));
}
