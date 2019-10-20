#include "FilesMonitorApp.h"
#include <QThread>
#include "../Worker.h"
#include <QDebug>
using namespace std;

FilesMonitorApp::FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory, QObject *parent) :
    QObject(parent),
    _rootDir(rootDirectory),
    _archDir(archiveDirectory),
    _worker(nullptr),
    _thread(),
    _filesMap(),
    _fileScanner(rootDirectory)
{
    connect(&_fileScanner, &FileScanner::fileModified, this, &FilesMonitorApp::onFileModified);
    connect(&_fileScanner, &FileScanner::newFileAdded, this, &FilesMonitorApp::onNewFileAdded);
    connect(&_fileScanner, &FileScanner::fileRemoved, this, &FilesMonitorApp::onFileRemoved);

    /*
     *  połączyć fileScannera z connectami, tak, żeby za pierwszym razem już szły wiadomości newFileAdded !!!!
     *
    */

    //connect(_thread,    &QThread::started,  _worker,    &Worker::process);
    //connect(_worker,    &Worker::finished,  _thread,    &QThread::quit);
//    connect(_worker,    &Worker::finished,  _worker,    &Worker::deleteLater);
//    connect(_thread,    &QThread::finished, _thread,    &QThread::deleteLater);
    //connect(_worker,    &Worker::finished,  this, [this]{ qDebug() << "WARN: received finished signal. Calling deleteLater on Worker. "; _worker->deleteLater(); });
    //connect(_thread,    &QThread::finished, this, [this]{ qDebug() << "WARN: received finished signal. Calling deleteLater on Thread. "; _thread->deleteLater(); });
    //_thread->start();
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

void FilesMonitorApp::setupOneThread(const QString& file)
{
    _worker = new Worker(1);

    _worker->moveToThread(&_thread);
//    connect(_thread,    &QThread::started,  _worker,    &Worker::process);
//    connect(_worker,    &Worker::finished,  this, [this]{ qDebug() << "WARN: received finished signal. Calling deleteLater on Worker. "; _worker->deleteLater(); });
//    connect(_thread,    &QThread::finished, this, [this]{ qDebug() << "WARN: received finished signal. Calling deleteLater on Thread. "; _thread->deleteLater(); });
    connect(&_thread, &QThread::finished, _worker, &QObject::deleteLater);
    connect(_worker, &Worker::resultReady, this, &FilesMonitorApp::onResultReady);
    connect(_worker, &Worker::resultReady, &_thread, &QThread::quit);
    connect(_worker, &Worker::resultReady, this, [this]{ qDebug() << "Odebralem THread::quit() signal"; _thread.quit(); });
    _thread.start();
    _worker->process();
}

FilesMonitorApp::~FilesMonitorApp()
{
    delete _worker;
    _thread.quit();
    _thread.wait();
    //delete _thread;
}
