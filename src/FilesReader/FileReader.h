#ifndef FILEREADER_H
#define FILEREADER_H
#include <QString>
#include <QFile>
#include <QHash>

class QTimer;

class FileReader : public QObject
{
    Q_OBJECT
public:
    FileReader(const QString& rootDir);
    virtual ~FileReader() ;

private:
    QFile _rootFile;

    
};

#endif // FILEREADER_H
