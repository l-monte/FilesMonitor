#include <QCoreApplication>
#include "FilesMonitorApp.h"
#include "MonitorConfig.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include "Logger.h"
#include "../test/UnitTestFramework.h"

constexpr bool IS_UNIT_TEST_MODE = true;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (not IS_UNIT_TEST_MODE)
    {
        if (argc != ENTRY_PARAM_NUMBER)
        {
            qDebug() << "ERROR: The parameters number is wrong!";
            Logger::instance().log(Logger::ERROR, "The parameters number is wrong!");
            a.quit();

            return -1;
        }

        if ( (not QDir(argv[1]).exists()) or (not QDir(argv[2]).exists()) or
              (not QFileInfo(argv[1]).isDir()) or (not QFileInfo(argv[1]).isDir()) )
        {
            qDebug() << "ERROR: One of passed directories isn't exist.";
            Logger::instance().log(Logger::ERROR, "One of passed directories isn't exist.");
            a.quit();

            return -1;
        }

        FilesMonitorApp app(argv[1], argv[2], &a);

    }
    else
    {
        UnitTestFramework utFramework;
        utFramework.runUT();
    }

    return a.exec();
}

