#include "FileReader.h"
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileReader::FileReader(const QString& rootDir) :
    _rootFile(rootDir)
{

}

//void FileReader::scanFiles()
//{
//    qDebug() << "LOG: FileReader.cpp : scanFiles() - start function";
//    QDir directory(QFileInfo(_rootFile.fileName()).absoluteFilePath());
//    QStringList files = directory.entryList(QDir::Files);

//    if (files.size() > 0)               // TODO
//        qDebug() << "\nLista plikow:";

//    foreach(QString fileName, files) {
//        _filesMap.insert(fileName, true);
//        qDebug() << "Plik: " << fileName;
//    }
//}

FileReader::~FileReader()
{
    //delete _scanningFileTimer;
}
