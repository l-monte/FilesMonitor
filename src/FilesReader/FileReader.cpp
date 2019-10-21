#include "FileReader.h"
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileReader::FileReader(const QString& filePath) :
    _file(filePath)
{
}

void FileReader::readFile()
{
    qDebug() << "[FileReader::readFile] Reading " << _file.fileName() << " file...";

    if (_file.open(QFile::ReadOnly)) {
        char buf[4 * 400];      // 1 MB

        QTextStream in(&_file);
        while (!in.atEnd())
        {
           QString line = in.readLine();
           ...
        }
        inputFile.close();

        qDebug() << "[FileReader::readFile] Pos of current file: " << _file.pos() << ".";
    }


}

      /*
       * QFile inputFile(fileName);
      if (inputFile.open(QIODevice::ReadOnly))
      {
         QTextStream in(&inputFile);
         while (!in.atEnd())
         {
            QString line = in.readLine();
            ...
         }
         inputFile.close();
      }

      */
