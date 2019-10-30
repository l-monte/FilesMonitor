# FilesMonitor

**The project is implemented using qmake tool. It bases on C++17 version.**

The following points must be meet to build and run the application:
* download the newest version of Qt SDK and Qt Creator
* during Qt SDK installation, check which Qt Version do you install. Application uses 5.12.3 Qt version
* download and install MinGW 7.3.0 64-bit (it supports C++17)


Then, open your Qt Creator click File -> "Open File or Project..." and choose Qt Project File.


**The project assumptions:**
* The application works as a deamon
* The application takes two params - first is path to log directory, the second is path to archive folder
* Each file after read operation is deleted. New logs in this file create the new file with the same name
* There is config file where the following params could be changed (MonitorConfig.h file):
    * line length limitation
    * number of threads
    * REST peer address
    * number of read lines from file as one chunk
