#include "FilesMonitorApp.h"
#include <QThread>
#include "../Worker.h"
using namespace std;

FilesMonitorApp::FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory, QObject *parent) :
    QObject(parent),
    _rootDir(rootDirectory),
    _archDir(archiveDirectory),
    _worker(new Worker("C:/Projekty/Interview/FilesMonitor/FilesMonitor/Root/logs_16-10-19_1.txt")),
//                                                            //TODO change path !!!!!!!!!!!!!!!!!!!
//    _thread(new QThread()),
    _fileScanner(rootDirectory)
{
//    _worker->moveToThread(_thread);
//    connect(_thread,    &QThread::started,  _worker,    &Worker::process);
//    connect(_worker,    &Worker::finished,  _thread,    &QThread::quit);
//    connect(_worker,    &Worker::finished,  _worker,    &Worker::deleteLater);
//    connect(_thread,    &QThread::finished, _thread,    &QThread::deleteLater);
//    _thread->start();
}

FilesMonitorApp::~FilesMonitorApp()
{
    delete _worker;
    //delete _thread;
}
