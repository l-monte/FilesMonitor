#ifndef TASK_H
#define TASK_H

#include "FilesReader/FileReader.h"
#include "ArchiveWriter/ArchiveWriter.h"
#include "DataSender/DataSender.h"
#include "MonitorDefs.h"
#include <QRunnable>
#include <QObject>
#include <functional>

class Task
{
public:
    Task(const WorkerData& data);

    void run();

private:
    QString _filePath;
    QString _archivePath;
    QString _endpointAddr;

//    FileReader _reader;
//    ArchiveWriter _writer;
    DataSender _sender;
};

#endif // TASK_H
