#include <QCoreApplication>
#include "FilesMonitorApp/FilesMonitorApp.h"
#include "MonitorConfig.h"
#include <QDebug>                               // TODO
#include <QDir>
#include "FileScanner.h"        // TODO przenieść do App
#include <QThreadPool>
#include <QFileInfo>

//====================================
#include "dupa.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != ENTRY_PARAM_NUMBER)
    {
        qDebug() << "ERROR: The parameters number is wrong!";
        a.quit();

        return -1;
    }

    if ( (not QDir(argv[1]).exists()) or (not QDir(argv[2]).exists()) or
          (not QFileInfo(argv[1]).isDir()) or (not QFileInfo(argv[1]).isDir()) )
    {
        qDebug() << "ERROR: One of passed directories isn't exist.";
        a.quit();

        return -1;
    }

    qDebug() << "WorkerThread() testowanie ------------------------------";

//    Runner* r = new Runner();
//    r->operate();
//    delete r;

    qDebug() << "WorkerThread() testowanie ------------------------------";
    FilesMonitorApp app(argv[1], argv[2], &a);

    return a.exec();
}

