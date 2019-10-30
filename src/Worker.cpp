#include "Worker.h"
#include "FileReader.h"
#include "ArchiveWriter.h"
#include "MonitorConfig.h"
#include "MonitorDefs.h"
#include "FilesMonitorApp.h"
#include <QEventLoop>
#include "DataSender.h"

Worker::Worker(const WorkerSetupData& data) :
    _logFile(data.filePath),
    _archiveFile(data.archivePath)
{
}

void Worker::run()
{
    FileReader reader(_logFile.fileName());
    ArchiveWriter writer(_archiveFile.fileName());
    DataSender sender;
    QEventLoop loop;

    connect(&reader, &FileReader::sendReadData, &writer, &ArchiveWriter::write);
    connect(&reader, &FileReader::sendReadData, &sender, &DataSender::send);
    connect(&sender, &DataSender::finished, &loop, &QEventLoop::quit);

    reader.readFile();

    loop.exec();

    emit finished(retrieveLogFileName());
}

QString Worker::retrieveLogFileName() const
{
    QFileInfo info(_logFile);
    return info.fileName();
}
