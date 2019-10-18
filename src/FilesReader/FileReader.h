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

public slots:
    void scanFiles();

private:
    QFile _rootFile;

    QTimer* _scanningFileTimer;
    QHash<QString, bool> _filesMap;
};

#endif // FILEREADER_H
