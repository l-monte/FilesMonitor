QT -= gui
QT += widgets network testlib

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/FileScanner.cpp \
    src/ArchiveWriter.cpp \
    src/DataSender.cpp \
    src/FileReader.cpp \
    src/Logger.cpp \
    src/main.cpp \
    src/Worker.cpp \
    src/FilesMonitorApp.cpp \
    test/FileReaderTestSuite.cpp \
    test/UnitTestFramework.cpp

HEADERS += \
    src/FileScanner.h \
    src/ArchiveWriter.h \
    src/DataSender.h \
    src/FilesMonitorApp.h \
    src/FileReader.h \
    src/Logger.h \
    src/MonitorConfig.h \
    src/MonitorDefs.h \
    src/Worker.h \
    test/FileReaderTestSuite.h \
    test/UnitTestFramework.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
