#ifndef LOGGER_H
#define LOGGER_H
#include <QThread>
#include "MonitorConfig.h"
#include <QDebug>
#include <mutex>
#include <QFile>

#define LOG(type, txt) Logger::instance().log(type, txt, __FILE__);

enum LOG_LEVEL
{
    INFO,
    WARN,
    ERROR
};

class Logger
{
public:

    static Logger& instance();

    void log(LOG_LEVEL lvl, const QString& txt, const QString& file);

private:
    void saveToFile(const QString& log);
    QString getLevel(LOG_LEVEL sev) const;

private:
    Logger();
    QFile _file;
    std::mutex _mutex;
};

#endif // LOGGER_H
