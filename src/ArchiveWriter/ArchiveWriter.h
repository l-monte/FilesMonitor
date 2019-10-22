#ifndef ARCHIVEWRITER_H
#define ARCHIVEWRITER_H
#include <QString>
#include <QFile>

class ArchiveWriter : public QObject
{
    Q_OBJECT
public:
    ArchiveWriter(const QString& archDir);

    void write(const QList<QString>& logChunk);
private:
    QFile _file;
};

#endif // ARCHIVEWRITER_H
