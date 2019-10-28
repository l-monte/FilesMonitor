#ifndef LOGGER_H
#define LOGGER_H
#include <QThread>
#include "MonitorConfig.h"
#include <QDebug>
#include <mutex>
#include <QFile>

class Logger
{
public:

    enum LOG_LEVEL
    {
        INFO,
        WARN,
        ERROR
    };

    static Logger& instance();

    void log(LOG_LEVEL lvl, const QString& txt);

private:
    void saveToFile(const QString& log);
    QString getLevel(LOG_LEVEL sev) const;

private:
    Logger();
    QFile _file;
    std::mutex _mutex;
};

#endif // LOGGER_H
