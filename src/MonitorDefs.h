#ifndef MONITORDEFS_H
#define MONITORDEFS_H
#include <QStringList>

struct WorkerData
{
    const QString filePath;
    const QString archivePath;
};

struct LogData
{
    const QString fileName;
    QStringList logData;
};

#endif // MONITORDEFS_H
