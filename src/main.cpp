#include <QCoreApplication>
#include "FilesMonitorApp.h"
#include "MonitorConfig.h"
#include <QFileInfo>
#include "Logger.h"
#include "../test/UnitTestFramework.h"
#include "MonitorConfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (IS_UNIT_TEST_MODE)
    {
        UnitTestFramework utFramework;
        utFramework.runUT();
    }

    if (argc != (ENTRY_PARAM_NUMBER + 1))
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

    FilesMonitorApp app(argv[1], argv[2], &a);

    return a.exec();
}

