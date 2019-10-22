#include "ArchiveWriter.h"
#include <QDebug>

ArchiveWriter::ArchiveWriter(const QString& archDir) : _file(archDir)
{

}

void ArchiveWriter::write(const QList<QString>& logChunk)
{
    qDebug() << "\tINFO: [ArchiveWriter::write] received log portion from FileReader";
    qDebug() << "\tINFO: [ArchiveWriter::write] archive folder full path: " << _file.fileName();


    if (_file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "\tINFO: [ArchiveWriter::write] _file is successfully opened.";
        QTextStream output(&_file);

        for (auto line: logChunk)
        {
            output << line << "\n";
        }
        _file.close();
    }
    else
        qDebug() << "\tERROR: [ArchiveWriter::write] _file is unable to open.";

    qDebug() << "\tINFO: [ArchiveWriter::write] chunk logs written";
}
