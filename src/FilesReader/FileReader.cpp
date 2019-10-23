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
namespace
{
constexpr unsigned int LINE_NUMBER_IN_ONE_CHUNK = 1310;
}

void FileReader::readFile()
{
    if (_file.open(QFile::ReadOnly | QFile::Text))
    {
        quint64 lineCnt = 1;
        QTextStream input(&_file);
        QList<QString> lines{};

        while (not input.atEnd())
        {
            lines.push_back(input.readLine(LOG_LINE_LENGTH));
            ++lineCnt;

            if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK == 0)
            {
                //_sendLogPortionHandler(lines);
                emit receivedLogsForFurtherProcessing(lines.last());         // TODO
            }
        }
        if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK != 0)
        {
            qDebug() << "Emituje tu cos kur*a?";
            emit receivedLogsForFurtherProcessing(lines.last());         // TODO
            _file.close();
        }
    }
}
