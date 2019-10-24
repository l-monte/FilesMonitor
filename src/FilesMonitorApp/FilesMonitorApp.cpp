#include "FilesMonitorApp.h"
#include <QThread>
#include "../Worker.h"
#include <QDebug>
#include "../MonitorConfig.h"
#include <QApplication>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>
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
        Worker *worker = new Worker(this, WorkerData{_rootDir.absoluteFilePath() + "/" + file, _archDir.absoluteFilePath() + "/" + file, "192.168.54.2"} );       // TODO
        worker->setAutoDelete(true);

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

FilesMonitorApp::~FilesMonitorApp()
{
}

void FilesMonitorApp::sendDataToEndpoint(const QList<QString>& data)
{
    qDebug() << "\t[FilesMonitorApp::sendDataToEndpoint] start of function\n";
    QUrl serviceUrl = QUrl("http://monte.free.beeceptor.com/test1/testFile");
    QNetworkRequest request(serviceUrl);
    QJsonObject json;
    for (auto it = data.begin(); it != data.end(); it++)
        json.insert("data", *it);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    _networkMgr.post(request, jsonData);
}
