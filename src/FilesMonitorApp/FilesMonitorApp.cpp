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
    _workers(),
    _threads(),
    _filesMap(),
    _fileScanner(rootDirectory)
{
    connect(&_fileScanner, &FileScanner::fileModified, this, &FilesMonitorApp::onFileModified);
    connect(&_fileScanner, &FileScanner::newFileAdded, this, &FilesMonitorApp::onNewFileAdded);
    connect(&_fileScanner, &FileScanner::fileRemoved, this, &FilesMonitorApp::onFileRemoved);
    _fileScanner.scanFiles();

    for (int i = 0; i < THREAD_NUMBER; ++i)
    {
        _workers.push_back(new Worker(i+1));
        _threads.push_back(new QThread);
        _workers[i]->moveToThread(_threads[i]);

        connect(_workers[i], &Worker::resultReady, this, &FilesMonitorApp::onResultReady);
        //connect(this, &Runner::operate, worker, &Worker::process);
        //connect(worker, &Worker::resultReady, &_wThread, WorkerThread::quit);
        connect(&_wThread, &WorkerThread::finished, worker, &Worker::deleteLater);
        _threads[i]->start();
    }
}

void FilesMonitorApp::onNewFileAdded(const QString& file)
{
    static int counter = 1; // TODO - później usunać przy przejściu na wiele wątków
    qDebug() << "INFO: [FilesMonitorApp] got newFileAdded signal (file: " << file << ").";

    if (counter == 1)
    {
        setupOneThread(file);
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

void FilesMonitorApp::onResultReady(const QString& msg)
{
    qDebug() << "INFO: [FilesMonitorApp] got onResultReady signal (message: " << msg << ").";
}

FilesMonitorApp::~FilesMonitorApp()
{
    for (int i = 0; i < THREAD_NUMBER; ++i)
    {
//        _workers[i]->moveToThread(QApplication::instance()->thread());
//        delete _workers[i];
        _threads[i]->quit();
        _threads[i]->wait();
        //delete _threads[i];
        delete _threads[i];
    }
}
