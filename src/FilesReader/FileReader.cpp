#include "FileReader.h"
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileReader::FileReader(const QString& rootDir) :
    _rootFile(rootDir),
    _scanningFileTimer(new QTimer(this)),
    _filesMap()
{
    _scanningFileTimer->setSingleShot(false);
    _scanningFileTimer->setInterval(10000);
    _scanningFileTimer->start();                // TODO przenieść do funkcji start()

    connect(_scanningFileTimer, &QTimer::timeout, this, &FileReader::scanFiles);
}

void FileReader::scanFiles()
{
    qDebug() << "LOG: FileReader.cpp : scanFiles() - start function";
    QDir directory(QFileInfo(_rootFile.fileName()).absoluteFilePath());
    QStringList files = directory.entryList(QDir::Files);

    if (files.size() > 0)               // TODO
        qDebug() << "\nLista plikow:";

    foreach(QString fileName, files) {
        _filesMap.insert(fileName, true);
        qDebug() << "Plik: " << fileName;
    }
}

FileReader::~FileReader()
{
    delete _scanningFileTimer;
}
