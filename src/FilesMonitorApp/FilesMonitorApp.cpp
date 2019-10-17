#include "FilesMonitorApp.h"
#include <iostream>
using namespace std;

FilesMonitorApp::FilesMonitorApp(const QString& rootDirectory, const QString& archiveDirectory) :
    _rootDir(rootDirectory),
    _archDir(archiveDirectory),
    _reader(_rootDir.path()),
    _writer(_archDir.path()),
    _sender()
{}

void FilesMonitorApp::start()
{
    cout << "MONTE: boost!" << endl;
}
