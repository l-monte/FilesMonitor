#include "ArchiveWriter.h"
#include "MonitorDefs.h"
#include <QDebug>

ArchiveWriter::ArchiveWriter(const QString& archDir) : _file(archDir)
{
}

void ArchiveWriter::write(const LogData& data)
{
    if (_file.open(QFile::Append | QFile::Text))
    {
        QTextStream output(&_file);

        for (auto line: data.logData)       //TODO
        {
            output << line << "\n";
        }
        _file.close();
    }
    else
        qDebug() << "\tERROR: [ArchiveWriter::write] _file is unable to open.";
}

void ArchiveWriter::deleteFile() const
{
    if (not _file.remove(_file.fileName()))
        qDebug() << "ERROR: [ArchiveWriter::deleteFile]: nable to remove file: " + _file.fileName();
}
