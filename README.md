# FilesMonitor

Build an application in which will read logs files from a specific directory (set by parameter) then send the content of all logs to a REST endpoint. After sending archive already sent logs -  move them to ‘archived’ directory.

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
* The following REST endpoint address is set now: http://monte.free.beeceptor.com/ 
* There is config file where the following params could be changed (MonitorConfig.h file):
    * line length limitation
    * number of threads
    * REST peer address
    * number of read lines from file as one chunk
* Each file is read by another worker class
* After read whole file, worker removes such file from "root" directory
* There is an assumption that the file modification could occur during file reading


**Notes**
* There is only test suite UT for one class - I assumed that you want to see how I test the code, but taking into account my time limitations in last days I did such assumption. There were some configuration problems with UT framework dedicated for QT library, so I wrote some own, small test framework.
Of course, I have tested manually different scenarios for another classes. 
* I did not created interfaces to classes which is good practice, but it was dicated by simple application structure. I am open to discuss on this topic.
