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
    virtual ~FileReader() = default;

    bool readFile();

signals:
    void sendReadData(const LogData& logData);
    void deleteFile();

private:
    QFile _file;
};

#endif // FILEREADER_H
