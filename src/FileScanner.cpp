#include "FileScanner.h"
#include "MonitorConfig.h"
#include <QDebug>       // TODO
#include <QFileInfo>    // TODO

FileScanner::FileScanner(const QString& dirPath, QObject *parent) : QObject(parent),
    _rootDirectory(dirPath),
    _fileScanningTimer(new QTimer(this)),
    _watcher(this)
{
    //_rootDirectory.setNameFilters(QStringList() << QString(SUPPORTED_FILE_FORMAT));

//    _fileScanningTimer->setSingleShot(false);
//    _fileScanningTimer->setInterval(SCANNING_TIMER_INTERVAL);
//    _fileScanningTimer->start();

//    connect(_fileScanningTimer, &QTimer::timeout, this, [this]{ /*TODO*/qDebug() << "sending scanner timeout..."; emit scannerTimeout(); });

//    connect(&_watcher, &QFileSystemWatcher::directoryChanged, this, [this]{ qDebug() << "FileScanner: received directoryChanged() signal."; scanFiles(); });
//    connect(&_watcher, &QFileSystemWatcher::fileChanged, this, [&](const QString& name){ qDebug() << "fileChanged() : " << name; onFileChanged(name); });
    _watcher.addPath(dirPath);
}

void FileScanner::scanFiles()
{
    qDebug() << "INFO: [FileScanner] start of function";
    QStringList fileList = _rootDirectory.entryList(QDir::Files);

    for (int i = 0; i < fileList.size(); ++i)
    {
        if (isNewFile(fileList[i]))
        {
            qDebug() << "INFO: [FileScanner] Added new file: " << fileList[i];

            _watcher.addPath(_rootDirectory.path() + "/" + fileList[i]);

            qDebug() << "INFO: [FileScanner] powinno sie wyslac newFileAdded !??!?!?!?!?";
            emit newFileAdded(fileList[i]);
        }
    }
}

void FileScanner::onFileChanged(const QString& fileName)
{
    if (QFileInfo::exists(fileName))
    {
        qDebug() << "INFO: [FileScanner] emitting fileModified() signal.";
        emit fileModified(fileName);
    }
    else
    {
        qDebug() << "INFO: [FileScanner] Remove file: " << fileName;
        qDebug() << "INFO: [FileScanner] emitting fileRemoved() signal.";
        _watcher.removePath(fileName);
        emit fileRemoved(fileName);
    }
}

bool FileScanner::isNewFile(const QString& fileName) const
{
    return (not _watcher.files().contains(_rootDirectory.path() + "/" + fileName));
}

// TODO usunąć poniższe
/*
 *         QFile file(_rootDirectory.path() + "/" + fileList[i]);
        if (file.open(QIODevice::ReadWrite))
        {
            qDebug() << "File: " << file.fileName() << " opened!";

            QTextStream instream(&file);
            QString line = instream.readLine();

            qDebug() << "first line: " << line;
            file.close();
        }
        else
            qDebug() << "File: " << file.fileName() << " not opened..";
*/
