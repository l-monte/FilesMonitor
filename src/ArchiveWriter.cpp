#include "ArchiveWriter.h"
#include "MonitorDefs.h"
#include <QFileInfo>
#include "Logger.h"

ArchiveWriter::ArchiveWriter(const QString& archDir) : _file(archDir)
{
}

void ArchiveWriter::write(const LogData& data)
{
    if (_file.open(QFile::Append | QFile::Text))
    {
        QTextStream output(&_file);

        for (auto line: data.logData)
        {
            output << line << "\n";
        }
        _file.close();
    }
    else
    {
        QFileInfo fInfo(_file);
        LOG(ERROR, "Unable to open " + fInfo.fileName() + " file for writing")
    }
}

void ArchiveWriter::deleteFile() const
{
    if (not _file.remove(_file.fileName()))
    {
        QFileInfo fInfo(_file);
        LOG(ERROR, "Unable to delete " + fInfo.fileName() + " file")
    }
}
