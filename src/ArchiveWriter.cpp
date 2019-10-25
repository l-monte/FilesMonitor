#include "ArchiveWriter.h"
#include <QDebug>

ArchiveWriter::ArchiveWriter(const QString& archDir) : _file(archDir)
{
}

void ArchiveWriter::write(const QList<QString>& data)
{
    if (_file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream output(&_file);

        for (auto line: data)
        {
            output << line << "\n";
        }
        _file.close();
    }
    else
        qDebug() << "\tERROR: [ArchiveWriter::write] _file is unable to open.";
}
