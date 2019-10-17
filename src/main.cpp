#include <QCoreApplication>
#include "FilesMonitorApp/FilesMonitorApp.h"
#include "MonitorConfig.h"
#include <QDebug>                               // TODO
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != ENTRY_PARAM_NUMBER)
    {
        qDebug() << "ERROR: The parameters number is wrong!";
        a.quit();

        return -1;
    }

    if ( (not QDir(argv[1]).exists()) or (not QDir(argv[2]).exists()) )
    {
        qDebug() << "ERROR: One of passed directories isn't exist.";
        a.quit();

        return -1;
    }

    FilesMonitorApp app(argv[1], argv[2]);
    app.start();

    return a.exec();
}
