#ifndef FILESCANNER_H
#define FILESCANNER_H

#include <QObject>
#include <QDir>
#include <QFileSystemWatcher>

class FileScanner : public QObject
{
    Q_OBJECT
public:
    explicit FileScanner(const QString& dirPath, QObject *parent = nullptr);

    void scanFiles();

signals:
    void newFileAdded(const QString& fileName);
    void fileModified(const QString& fileName);
    void fileRemoved(const QString& fileName);

private slots:
    void onFileChanged(const QString& fileName);

private:
    bool isNewFile(const QString& fileName) const;

private:
    QDir _rootDirectory;
    QFileSystemWatcher _watcher;
};

#endif // FILESCANNER_H
