#ifndef FILESMONITORAPP_H
#define FILESMONITORAPP_H
#include <QFileInfo>
#include "../FilesReader/FileReader.h"
#include "../ArchiveWriter/ArchiveWriter.h"
#include "../DataSender/DataSender.h"

class FilesMonitorApp
{
public:
    FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory);

    void start();

private:
    QFileInfo _rootDir;
    QFileInfo _archDir;

    FileReader _reader;
    ArchiveWriter _writer;
    DataSender _sender;
};

#endif // FILESMONITORAPP_H
