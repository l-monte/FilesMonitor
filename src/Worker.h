#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "FilesReader/FileReader.h"
#include "ArchiveWriter/ArchiveWriter.h"
#include "DataSender/DataSender.h"

class QString;

// TODO wydzielić do interfejsu Worker'a

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(const QString& filePath);
    ~Worker();

public slots:
    void process();

signals:
    void finished();

private:
    static int _id;
    const QString _filePath;

    FileReader _reader;
    ArchiveWriter _writer;
    DataSender _sender;
};

#endif // WORKER_H
