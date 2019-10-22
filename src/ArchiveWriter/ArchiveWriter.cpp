#include "ArchiveWriter.h"
#include <QDebug>

ArchiveWriter::ArchiveWriter(const QString& archDir) : _archDir(archDir)
{

}

void ArchiveWriter::write(const QString& logChunk)
{
    qDebug() << "\tINFO: [ArchiveWriter::onSendLogChunk] received log portion from FileReader: " << logChunk;


}
