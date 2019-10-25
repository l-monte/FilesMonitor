#include "Worker.h"
#include <QDebug>
#include "FileReader.h"
#include "ArchiveWriter.h"
#include "MonitorConfig.h"
#include "MonitorDefs.h"
#include "FilesMonitorApp.h"
#include <QEventLoop>
#include "DataSender.h"

namespace
{
constexpr unsigned int LINE_NUMBER_IN_ONE_CHUNK = 1310;
}

Worker::Worker(const WorkerData& data) :
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

    qDebug() << "\t[Worker::run()] end of function. ";
    emit finished(_logFile.fileName());
}
