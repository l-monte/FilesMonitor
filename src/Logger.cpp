#include "Logger.h"

Logger::Logger() : _file(DEBUG_FILE)
{
    if (_file.exists())
        _file.remove();
}

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::log(LOG_LEVEL lvl, const QString& txt)
{
    std::lock_guard<std::mutex> guard(_mutex);
    QString logStr = "[" + QString::number((long long)QThread::currentThread()) + "] " +
            getLevel(lvl) + " " + __FILE__ + ":" + __LINE__ + " " + txt;

    qDebug() << logStr;

    if (WRITE_TO_FILE_FLAG)
        saveToFile(logStr);
}

void Logger::saveToFile(const QString& log)
{
    if (_file.open(QFile::Append | QFile::Text))
    {
        QTextStream output(&_file);

        output << log;

        _file.close();
    }
    else
        qDebug() << "\tERROR: [Logger::saveToFile] _file is unable to open.";
}

QString Logger::getLevel(LOG_LEVEL lvl) const
{
    if (LOG_LEVEL::INFO == lvl) return "INFO";
    if (LOG_LEVEL::WARN == lvl) return "WARN";
    if (LOG_LEVEL::ERROR == lvl) return "ERROR";

    return "UNKNOWN_LVL";
}
