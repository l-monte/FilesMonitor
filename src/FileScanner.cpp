#include "FileScanner.h"
#include "MonitorConfig.h"
#include "Logger.h"

FileScanner::FileScanner(const QString& dirPath, QObject *parent) : QObject(parent),
    _rootDirectory(dirPath),
    _watcher(this)
{
    connect(&_watcher, &QFileSystemWatcher::directoryChanged, this, [this]{ scanFiles(); });
    connect(&_watcher, &QFileSystemWatcher::fileChanged, this, [&](const QString& name){ onFileChanged(name); });
    _watcher.addPath(dirPath);
}

void FileScanner::scanFiles()
{
    QStringList fileList = _rootDirectory.entryList(QDir::Files);

    if (fileList.empty())
        LOG(INFO, "File list is empty")

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
