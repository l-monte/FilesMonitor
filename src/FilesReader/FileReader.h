#ifndef FILEREADER_H
#define FILEREADER_H
#include <QString>
#include <QFile>

class FileReader
{
public:
    FileReader(const QString& rootDir);

private:
    QFile _rootFile;
};

#endif // FILEREADER_H
