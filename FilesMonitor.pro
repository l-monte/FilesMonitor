QT -= gui
QT += widgets network

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
    src/ArchiveWriter/ArchiveWriter.cpp \
    src/DataSender/DataSender.cpp \
    src/FilesReader/FileReader.cpp \
    src/GlobalDataSender.cpp \
    src/MonitorConfig.cpp \
    src/main.cpp \
    src/Worker.cpp \
    src/FilesMonitorApp/FilesMonitorApp.cpp

HEADERS += \
    src/FileScanner.h \
    src/ArchiveWriter/ArchiveWriter.h \
    src/DataSender/DataSender.h \
    src/FilesMonitorApp/FilesMonitorApp.h \
    src/FilesReader/FileReader.h \
    src/GlobalDataSender.h \
    src/MonitorConfig.h \
    src/MonitorDefs.h \
    src/Worker.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
