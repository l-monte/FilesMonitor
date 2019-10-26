#include "FilesMonitorApp.h"
#include <QThread>
#include "Worker.h"
#include <QDebug>
#include "MonitorConfig.h"
#include <QApplication>
using namespace std;

namespace
{
constexpr quint64 START_LINE_NUMBER = 0;
}

FilesMonitorApp::FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory, QObject *parent) :
    QObject(parent),
    _rootDir(rootDirectory),
    _archDir(archiveDirectory),
    _threadPool(this),
    _fileScanner(rootDirectory),
    _fileToWorkerStateMap({})
{
    _threadPool.setMaxThreadCount(THREAD_NUMBER);

    connect(&_fileScanner, &FileScanner::fileModified, this, &FilesMonitorApp::onFileModified);
    connect(&_fileScanner, &FileScanner::newFileAdded, this, &FilesMonitorApp::onNewFileAdded);
    connect(&_fileScanner, &FileScanner::fileRemoved, this, &FilesMonitorApp::onFileRemoved);
    _fileScanner.scanFiles();
}

void FilesMonitorApp::onNewFileAdded(const QString& fileName)
{
    qDebug() << "INFO: [FilesMonitorApp::onNewFileAdded] got onNewFileAdded signal (file: " << fileName << ").";
    Worker *worker = new Worker(WorkerSetupData{_rootDir.absoluteFilePath() + "/" + fileName, _archDir.absoluteFilePath() + "/" + fileName} );
    worker->setAutoDelete(true);

    connect(worker, &Worker::finished, this, &FilesMonitorApp::onWorkerFinished, Qt::QueuedConnection);

    _threadPool.start(worker);

    _fileToWorkerStateMap.insert(fileName, WorkerState::RUNNING);
}

void FilesMonitorApp::onFileModified(const QString& fileName)
{
    qDebug() << "INFO: [FilesMonitorApp::onFileModified] got fileModified signal (file: " << fileName << ").";

    if (not _fileToWorkerStateMap.contains(fileName))
    {
        qDebug() << "INFO: [FilesMonitorApp::onFileModified] file is not contained in the map -> calling onNewFileAdded slot.";
        onNewFileAdded(fileName);
        return;
    }

    if (WorkerState::FILE_DELETED == _fileToWorkerStateMap.value(fileName))
    {
        qDebug() << "INFO: [FilesMonitorApp::onFileModified] file is deleted -> calling onNewFileAdded slot.";
        onNewFileAdded(fileName);
        return;
    }
}
void FilesMonitorApp::onFileRemoved(const QString& fileName)
{
    qDebug() << "INFO: [FilesMonitorApp::onFileRemoved] got fileRemoved signal (file: " << fileName << ").";

    _fileToWorkerStateMap.insert(fileName, WorkerState::FILE_DELETED);
}

void FilesMonitorApp::onWorkerFinished(const QString& fileName)
{
    qDebug() << "INFO: [FilesMonitorApp::onWorkerFinished] Received filename is: " + fileName;

    _fileToWorkerStateMap.insert(fileName, WorkerState::FILE_DELETED);
}

FilesMonitorApp::~FilesMonitorApp()
{
}
