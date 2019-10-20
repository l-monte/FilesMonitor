#ifndef FILESCANNER_H
#define FILESCANNER_H

#include <QObject>
#include <QTimer>
#include <QDir>
#include <QFileSystemWatcher>

class FileScanner : public QObject
{
    Q_OBJECT
public:
    explicit FileScanner(const QString& dirPath, QObject *parent = nullptr);

    void scanFiles();

signals:
    void scannerTimeout();      // TODO do usunięcia
    void newFileAdded(const QString& fileName);
    void fileModified(const QString& fileName);
    void fileRemoved(const QString& fileName);

private slots:
    void onFileChanged(const QString& fileName);

private:
    bool isNewFile(const QString& fileName) const;

private:
    QDir _rootDirectory;
    QTimer* _fileScanningTimer;
    QFileSystemWatcher _watcher;        // TODO zastanowić się, czy tworzyć takie rzeczy jako membery, czy wskaźniki
};

#endif // FILESCANNER_H
