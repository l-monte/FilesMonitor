#include "FilesMonitorApp.h"
#include <QThread>
#include "Worker.h"
#include "Logger.h"
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
    Worker *worker = new Worker(WorkerSetupData{_rootDir.absoluteFilePath() + "/" + fileName, _archDir.absoluteFilePath() + "/" + fileName} );
    worker->setAutoDelete(true);

    connect(worker, &Worker::finished, this, &FilesMonitorApp::onWorkerFinished, Qt::QueuedConnection);

    _threadPool.start(worker);

    LOG(INFO, "Starting new Worker for " + fileName + " file")

    _fileToWorkerStateMap.insert(fileName, WorkerState::RUNNING);
}

void FilesMonitorApp::onFileModified(const QString& fileName)
{
    if (not _fileToWorkerStateMap.contains(fileName))
    {
        onNewFileAdded(fileName);
        return;
    }

    if (WorkerState::FILE_DELETED == _fileToWorkerStateMap.value(fileName))
    {
        onNewFileAdded(fileName);
        return;
    }
}
void FilesMonitorApp::onFileRemoved(const QString& fileName)
{
    _fileToWorkerStateMap.insert(fileName, WorkerState::FILE_DELETED);
}

void FilesMonitorApp::onWorkerFinished(const QString& fileName)
{
    QFileInfo fInfo(fileName);
    LOG(INFO, "Worker finished processing of file: " + fInfo.fileName())

    _fileToWorkerStateMap.insert(fileName, WorkerState::FILE_DELETED);
}

FilesMonitorApp::~FilesMonitorApp()
{
}
