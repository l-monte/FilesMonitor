#include "Worker.h"
#include <QString>
#include <QDebug>       // TODO
#include <QFile>
#include "MonitorConfig.h"
#include "MonitorDefs.h"
#include "FilesMonitorApp/FilesMonitorApp.h"

namespace
{
constexpr unsigned int LINE_NUMBER_IN_ONE_CHUNK = 1310;
}

Worker::Worker(FilesMonitorApp* mainApp, const WorkerData& data) :
    _logFile(data.filePath),
    _archiveFile(data.archivePath),
    _mainApp(mainApp)
{
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
                sendDataToRESTendpoint(lines);
                write(lines);
            }
        }
        if (lineCnt % LINE_NUMBER_IN_ONE_CHUNK != 0)
        {
            write(lines);
            sendDataToRESTendpoint(lines);
            _logFile.close();
        }
    }
}

void Worker::sendDataToRESTendpoint(const QList<QString>& data)
{
    qDebug() << "[Worker::sendDataToRESTendpoint] calling invoke method.";
    QMetaObject::invokeMethod(_mainApp, [=]{ _mainApp->sendDataToEndpoint(data); }, Qt::QueuedConnection);
}

