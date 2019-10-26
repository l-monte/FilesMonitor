#include "FileReader.h"
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "MonitorConfig.h"
#include "MonitorDefs.h"

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
        QFileInfo fileInfo(_file);
        LogData data{fileInfo.fileName(), {}};

        while (not input.atEnd())
        {
            data.logData.push_back(input.readLine(LOG_LINE_LENGTH));
            ++lineCnt;

            if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK == 0)
            {
                emit sendReadData(data);
                data.logData.clear();
            }
        }
        if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK != 0)
        {
            emit sendReadData(data);
            data.logData.clear();
            _file.close();
        }
    }
}
