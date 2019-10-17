#ifndef ARCHIVEWRITER_H
#define ARCHIVEWRITER_H
#include <QString>
#include <QFile>

class ArchiveWriter
{
public:
    ArchiveWriter(const QString& archDir);

private:
    QFile _archDir;
};

#endif // ARCHIVEWRITER_H
