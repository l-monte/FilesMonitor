#include "FileReader.h"
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include "MonitorConfig.h"
#include "MonitorDefs.h"
#include <QThread>
#include "Logger.h"

FileReader::FileReader(const QString& filePath) :
    _file(filePath)
{
}

// TODO: 2 MB -> 2097152 B -> 2 097 152 / (400 chars * 4B) ~ 1310
namespace
{
constexpr unsigned int LINE_NUMBER_IN_ONE_CHUNK = 1310;
}

bool FileReader::readFile()
{
    if (_file.open(QFile::ReadOnly | QFile::Text))
    {
        bool isFileDeleted = false;
        quint64 lineCnt = 1;
        QTextStream input(&_file);
        QFileInfo fileInfo(_file);
        LogData data{fileInfo.fileName(), {}};

        while (not input.atEnd())
        {
            if (not _file.exists())
            {
                emit deleteFile();
                isFileDeleted = true;
                break;
            }

            data.logData.push_back(input.readLine(LOG_LINE_LENGTH));
            ++lineCnt;

            if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK == 0)
            {
                emit sendReadData(data);
                data.logData.clear();
            }
        }
        if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK != 0 and isFileDeleted == false)
        {
            emit sendReadData(data);
            data.logData.clear();
            if (not _file.remove())
                LOG(ERROR, "Error during removing " + fileInfo.fileName() + " file")

        }
    }
    else
    {
        LOG(ERROR, "The destination " + _file.fileName() + " file unable to open")
        return false;
    }
    return true;
}
