#include "Worker.h"
#include <QString>
#include <QDebug>       // TODO
#include <QDir>

Worker::Worker(unsigned int id) :
    _id(id),
    _filePath(""),
    _reader(""),        // TODO
    _writer(""),        // TODO
    _sender()           // TODO
{
    qDebug() << "Worker() with id: " << _id << " received file path: " << _filePath;
}

Worker::~Worker()
{
    qDebug() << "Deleting Worker with id: " << _id << ".";
}

void Worker::process()
{
    qDebug() << "Worker[" << _id << "]::process()";



    emit resultReady("koncze prace");
}

void Worker::setPath(const QString& path)
{
    _filePath = path;
}
