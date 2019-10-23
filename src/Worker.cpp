#include "Worker.h"
#include <QString>
#include <QDebug>       // TODO
#include <QFile>
#include "MonitorConfig.h"
#include "MonitorDefs.h"

namespace
{
constexpr unsigned int LINE_NUMBER_IN_ONE_CHUNK = 1310;
}

Worker::Worker(QNetworkAccessManager* networkMgr, const WorkerData& data) :
    _logFile(data.filePath),
    _archiveFile(data.archivePath),
    _networkMgr(networkMgr)
{
    //_reader._sendLogPortionHandler = [this](const QList<QString>& fileContent){ this->sendLogPortionHandler(fileContent); };
}

void Worker::run()
{
    read();
}

void Worker::write(const QList<QString>& logChunk)
{
    if (_archiveFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream output(&_archiveFile);

        for (auto line: logChunk)
        {
            output << line << "\n";
        }
        _archiveFile.close();
    }
    else
        qDebug() << "\tERROR: [Worker::write] Archive writer is unable to open.";
}

void Worker::read()
{
    if (_logFile.open(QFile::ReadOnly | QFile::Text))
    {
        quint64 lineCnt = 1;
        QTextStream input(&_logFile);
        QList<QString> lines{};

        while (not input.atEnd())
        {
            lines.push_back(input.readLine(LOG_LINE_LENGTH));
            ++lineCnt;

            if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK == 0)
            {
                write(lines);
            }
        }
        if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK != 0)
        {
            write(lines);
            _logFile.close();
        }
    }
}

void Worker::sendDataToRESTendpoint()
{

}

void Worker::sendLogPortionHandler(const QString& logs)
{
//    _writer.write(logs);
//    emit sendData(logs);
}

