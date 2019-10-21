#include "Worker.h"
#include <QString>
#include <QDebug>       // TODO
#include <QDir>

Worker::Worker(const WorkerData& data) :
    _filePath(data.filePath),
    _archivePath(data.archivePath),
    _endpointAddr(data.endpointAddr),
    _reader(data.filePath),
    _writer(data.archivePath)
    //_sender(data.endpointAddr)
{
    qDebug() << "[Worker::Worker] c-tor";
}

void Worker::run()
{
    qDebug() << "[Worker::run] Running worker for file: " << _filePath;
    _reader.readFile();
}

