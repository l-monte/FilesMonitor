#include "Logger.h"
#include <QFileInfo>
#include <QTime>
#include "MonitorConfig.h"

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

void Logger::log(LOG_LEVEL lvl, const QString& txt, const QString& file)
{
    std::lock_guard<std::mutex> guard(_mutex);

    QFileInfo fInfo(file);
    QString logStr = QTime::currentTime().toString() +
            "[" + QString().sprintf("%08p", QThread::currentThread()) + "] " +
            getLevel(lvl) + " " +
            fInfo.fileName() + ": " +
            txt;

    qDebug().noquote() << logStr;
    qDebug().noquote() << endl;

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
        qDebug().noquote() << "ERROR: file is unable to open for saving logs...";
}

QString Logger::getLevel(LOG_LEVEL lvl) const
{
    if (LOG_LEVEL::INFO == lvl) return "INFO";
    if (LOG_LEVEL::WARN == lvl) return "WARN";
    if (LOG_LEVEL::ERROR == lvl) return "ERROR";

    return "UNKNOWN_LVL";
}
