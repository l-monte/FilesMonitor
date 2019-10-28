#include "FileReaderTestSuite.h"
#include <QtTest/QSignalSpy>
#include <QtTest/QTest>
#include <QTextStream>
#include <QDebug>
#include <QFile>

namespace
{
const QString TEST_FILE_PATH = "dut_file.txt";
constexpr quint8 LINE_NUMBER_0 = 0;
constexpr quint8 LINE_NUMBER_1 = 1;
constexpr quint16 LINE_NUMBER_1500 = 1500;
}

FileReaderTestSuite::FileReaderTestSuite(QObject *parent) :
    QObject(parent),
    _dut(std::make_unique<FileReader>(TEST_FILE_PATH)),
    _dutFile(nullptr)
{

}

void FileReaderTestSuite::initTestCase()
{
    _dutFile = new QFile(TEST_FILE_PATH);
}

void FileReaderTestSuite::cleanUpTestCase()
{
    if (not _dutFile)
    {
        delete _dutFile;
        _dutFile = nullptr;
    }
}

Result FileReaderTestSuite::testCase_readEmptyFile_shouldEmitEmptyLogData()
{
    initTestCase();
    fillTestFile(LINE_NUMBER_0);

    qRegisterMetaType<LogData>();
    QSignalSpy sendDataSpy(_dut.get(), SIGNAL(sendReadData(const LogData&)));

    _dut->readFile();

    bool result = isTheSame(sendDataSpy.count(), 1);

    cleanUpTestCase();

    return {result, "readEmptyFile_shouldEmitEmptyLogData"};
}

Result FileReaderTestSuite::testCase_readFileWith1Line_shouldEmitFilledLogData()
{
    initTestCase();
    fillTestFile(LINE_NUMBER_1);

    qRegisterMetaType<LogData>();
    QSignalSpy sendDataSpy(_dut.get(), SIGNAL(sendReadData(const LogData&)));

    _dut->readFile();

    bool result = isTheSame(sendDataSpy.count(), 1);

    cleanUpTestCase();

    return {result, "readFileWith1Line_shouldEmitFilledLogData"};
}

Result FileReaderTestSuite::testCase_readFileWith1500Line_shouldEmitTwoSignals()
{
    initTestCase();
    fillTestFile(LINE_NUMBER_1500);

    qRegisterMetaType<LogData>();
    QSignalSpy sendDataSpy(_dut.get(), SIGNAL(sendReadData(const LogData&)));

    _dut->readFile();

    bool result = isTheSame(sendDataSpy.count(), 2);

    cleanUpTestCase();

    return {result, "readFileWith1500Line_shouldEmitTwoSignals"};
}

void FileReaderTestSuite::fillTestFile(quint64 linesNumber)
{
    if (_dutFile->open(QFile::Append | QFile::Text))
    {
        QTextStream stream(_dutFile);

        for (quint64 i = 1; i < linesNumber; ++i)
        {
            stream << "Test suite: FileReaderTestSuite - line number: " + QString::number(i);
            stream << endl;
        }

        _dutFile->close();
    }
    else
    {
        qDebug() << "ERROR: [FileReaderTestSuite] Test file " + _dutFile->fileName() << " not created!";
    }
}

template<typename T>
bool FileReaderTestSuite::isTheSame(T a1, T a2)
{
    return a1 == a2;
}
