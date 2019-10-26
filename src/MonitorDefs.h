#ifndef MONITORDEFS_H
#define MONITORDEFS_H
#include <QStringList>

using FileName = QString;

struct WorkerSetupData
{
    const QString filePath;
    const QString archivePath;
};

struct LogData
{
    const QString fileName;
    QStringList logData;
};

enum class WorkerState
{
    RUNNING,
    FILE_DELETED
};

struct WorkerInfo
{
    WorkerState state;
    quint64 readingFromLine;
};

#endif // MONITORDEFS_H
