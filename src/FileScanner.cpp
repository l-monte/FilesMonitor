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

    _fileScanningTimer->setSingleShot(false);
    _fileScanningTimer->setInterval(SCANNING_TIMER_INTERVAL);
    _fileScanningTimer->start();

    connect(_fileScanningTimer, &QTimer::timeout, this, [this]{ /*TODO*/qDebug() << "sending scanner timeout..."; emit scannerTimeout(); });

    connect(&_watcher, &QFileSystemWatcher::directoryChanged, this, [this]{ qDebug() << "FileScanner: received directoryChanged() signal."; scanFiles(); });
    connect(&_watcher, &QFileSystemWatcher::fileChanged, this, [&](const QString& name){ qDebug() << "fileChanged() : " << name; onFileChanged(name); });
    _watcher.addPath(dirPath);

    scanFiles();
}

void FileScanner::scanFiles()
{
    qDebug() << "INFO: [FileScanner] start of function";
    QStringList fileList = _rootDirectory.entryList(QDir::Files);

    if (fileList.size() == 0)               // TODO
        qDebug() << "\nERROR: [FileScanner] Nie znaleziono zadnych plikow.";

    for (int i = 0; i < fileList.size(); ++i)
    {
        if (isNewFile(fileList[i]))
        {
            qDebug() << "INFO: [FileScanner] Added new file: " << fileList[i];

            _watcher.addPath(_rootDirectory.path() + "/" + fileList[i]);
            emit newFileAdded(fileList[i]);
        }
    }

    /*for (int i = 0; i < fileList.size(); ++i)
    {
        //QString fileName = files.takeFirst();
        qDebug() << "INFO: scanFiles() file:" << fileList[i] <<" full path: " << (_rootDirectory.path() + "/" + fileList[i]);

        auto findResult = _allfilesMap.find(fileList[i]);
        if (findResult == _allfilesMap.end())
        {
            _allfilesMap.insert(fileList[i], true);
        }
        else
        {
            // TODO(usunąć później) do nothing
        }
    }*/
}

void FileScanner::onFileChanged(const QString& fileName)
{
    if (QFileInfo::exists(_rootDirectory.path() + "/" + fileName))
    {
        qDebug() << "INFO: [FileScanner] emitting fileModified() signal.";
        emit fileModified(fileName);
    }
    else
    {
        qDebug() << "INFO: [FileScanner] Remove file: " << fileName;
        _watcher.removePath(fileName);
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
