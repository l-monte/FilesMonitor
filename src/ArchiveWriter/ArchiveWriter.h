#ifndef ARCHIVEWRITER_H
#define ARCHIVEWRITER_H
#include <QString>
#include <QFile>

class ArchiveWriter : public QObject
{
    Q_OBJECT
public:
    ArchiveWriter(const QString& archDir);

    void write(const QString& logChunk);
private:
    QFile _archDir;
};

#endif // ARCHIVEWRITER_H
