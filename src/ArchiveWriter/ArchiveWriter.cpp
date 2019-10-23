#include "ArchiveWriter.h"
#include <QDebug>

ArchiveWriter::ArchiveWriter(const QString& archDir) : _file(archDir)
{

}

void ArchiveWriter::write(const QString& line)
{
    qDebug() << "\tINFO: [ArchiveWriter::write] received log portion from FileReader";

    if (_file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "\tINFO: [ArchiveWriter::write] _file is successfully opened.";
        QTextStream output(&_file);

        //for (auto line: logChunk)
        //{
            output << line << "\n";
        //}
        _file.close();
    }
    else
        qDebug() << "\tERROR: [ArchiveWriter::write] _file is unable to open.";

    qDebug() << "\tINFO: [ArchiveWriter::write] chunk logs written";
}
