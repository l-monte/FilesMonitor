#ifndef ARCHIVEWRITER_H
#define ARCHIVEWRITER_H
#include <QString>
#include <QFile>

struct LogData;

class ArchiveWriter : public QObject
{
    Q_OBJECT
public:
    ArchiveWriter(const QString& archDir);

public slots:
    void write(const LogData& datachunk);
    void deleteFile() const;

private:
    QFile _file;
};

#endif // ARCHIVEWRITER_H
