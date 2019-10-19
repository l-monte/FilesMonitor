#include "Worker.h"
#include <QString>
#include <QDebug>       // TODO
#include <QDir>

int Worker::_id = 0;

Worker::Worker(const QString& filePath) :
    _filePath(filePath),
    _reader(""),        // TODO
    _writer(""),        // TODO
    _sender()           // TODO
{
    _id++;
    qDebug() << "Worker() with id: " << _id << " received file path: " << _filePath;
}

Worker::~Worker()
{
    qDebug() << "Deleting Worker with id: " << _id << ".";
}

void Worker::process()
{
    qDebug() << "Worker[" << _id << "]::process()";


    //emit finished();
}
