#ifndef FILEREADER_H
#define FILEREADER_H
#include <QString>
#include <QFile>
#include <QHash>
#include <functional>

class QTimer;
struct LogData;

class FileReader : public QObject
{
    Q_OBJECT
public:
    FileReader(const QString& filePath);

    FileReader(const FileReader& o) = delete;
    FileReader(FileReader&& o) = delete;
    FileReader& operator=(const FileReader& o) = delete;
    FileReader& operator=(FileReader&& o) = delete;
    virtual ~FileReader() = default;

    void readFile();

signals:
    void sendReadData(const LogData& logData);

private:
    QFile _file;
};

#endif // FILEREADER_H
