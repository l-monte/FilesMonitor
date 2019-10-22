#include "FilesMonitorApp.h"
#include <QThread>
#include "../Worker.h"
#include <QDebug>
#include "../MonitorConfig.h"
#include <QApplication>
using namespace std;

FilesMonitorApp::FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory, QObject *parent) :
    QObject(parent),
    _rootDir(rootDirectory),
    _archDir(archiveDirectory),
    _threadPool(this),
    _fileScanner(rootDirectory)
{
    _threadPool.setMaxThreadCount(THREAD_NUMBER);

    connect(&_fileScanner, &FileScanner::fileModified, this, &FilesMonitorApp::onFileModified);
    connect(&_fileScanner, &FileScanner::newFileAdded, this, &FilesMonitorApp::onNewFileAdded);
    connect(&_fileScanner, &FileScanner::fileRemoved, this, &FilesMonitorApp::onFileRemoved);
    _fileScanner.scanFiles();
}

void FilesMonitorApp::onNewFileAdded(const QString& file)
{
    static int counter = 1; // TODO - później usunać przy przejściu na wiele wątków
    qDebug() << "INFO: [FilesMonitorApp] got newFileAdded signal (file: " << file << ").";

    if (counter == 1)
    {
        qDebug() << "[FilesMonitorApp::onNewFileAdded] starting thread pool for file: " << file;
        Worker *worker = new Worker( WorkerData{_rootDir.absoluteFilePath() + "/" + file, _archDir.absoluteFilePath() + "/" + file, "192.168.54.2"} );       // TODO
        worker->setAutoDelete(true);

        worker->_respHandler = [this](std::pair<QString, bool> msg){ this->respHandler(msg); };

        if (_threadPool.tryStart(worker))
            qDebug() << "[FilesMonitorApp::onNewFileAdded] thread pool started.";
        else
            qDebug() << "ERROR: [FilesMonitorApp::onNewFileAdded] New worker not started!";
    }

    counter++;
}

void FilesMonitorApp::onFileModified(const QString& file)
{
    qDebug() << "INFO: [FilesMonitorApp] got fileModified signal (file: " << file << ").";
}
void FilesMonitorApp::onFileRemoved(const QString& file)
{
    qDebug() << "INFO: [FilesMonitorApp] got fileRemoved signal (file: " << file << ").";
}

void FilesMonitorApp::respHandler(std::pair<QString, bool> respMsg)
{
    qDebug() << "[FilesMonitorApp::respHandler] received " << respMsg.second << " as finished status for file: " << respMsg.first;
}

FilesMonitorApp::~FilesMonitorApp()
{

}
