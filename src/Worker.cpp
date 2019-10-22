#include "Worker.h"
#include <QString>
#include <QDebug>       // TODO
#include <QDir>

Worker::Worker(const WorkerData& data) :
    _filePath(data.filePath),
    _archivePath(data.archivePath),
    _endpointAddr(data.endpointAddr),
    _reader(data.filePath),
    _writer(data.archivePath),
    _sender()
{
    qDebug() << "[Worker::Worker] c-tor";

    _reader._sendLogPortionHandler = [this](const QString& data){ this->sendLogPortionHandler(data); };
}

void Worker::run()
{
    qDebug() << "[Worker::run] Running worker for file: " << _filePath;
    _reader.readFile();
}

void Worker::sendLogPortionHandler(const QString& logs)
{
    _writer.write(logs);
    _sender.send(logs);
}

