#include "FileReader.h"
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "../MonitorConfig.h"
#include <QList>

FileReader::FileReader(const QString& filePath) :
    _file(filePath)
{
}

// TODO: 2 MB -> 2097152 B -> 2 097 152 / (400 chars * 4B) ~ 1310

void FileReader::readFile()
{
    qDebug() << "[FileReader::readFile] Reading " << _file.fileName() << " file...";

    if (_file.open(QFile::ReadOnly | QFile::Text))
    {
        quint64 lineCnt = 1;
        QTextStream input(&_file);
        QString line{};
        QList<QString> lines{};

        while (not input.atEnd())
        {
            lines.push_back(input.readLine(LOG_LINE_LENGTH));
            ++lineCnt;

            if (lineCnt % 1310 == 0)
            {
                qDebug() << "[FileReader::readFile] got logs portion. Calling _sendLogPortionHandler() callback.";
                _sendLogPortionHandler(lines);
            }
        }
        qDebug() << "\nDisplaing read lines:";
//        for (auto lineList : lines)
//        {
//            qDebug() << lineList;
//        }
        if (lineCnt % 1310 != 0)
        {
            _sendLogPortionHandler(lines);
            _file.close();
        }
    }
}
