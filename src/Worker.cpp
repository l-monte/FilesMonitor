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
    qDebug() << "[Worker::Worker] c-tor, current threadId = " + QThread::;

    _reader._sendLogPortionHandler = [this](const QList<QString>& fileContent){ this->sendLogPortionHandler(fileContent); };
}

void Worker::run()
{
    qDebug() << "[Worker::run] Running worker for file: " << _filePath;
    _reader.readFile();
}

void Worker::sendLogPortionHandler(const QList<QString>& logs)
{
    _writer.write(logs);
    _sender.send(logs);
}

