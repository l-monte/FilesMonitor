#include "FileReaderTestSuite.h"
#include <QtTest/QSignalSpy>
#include <QtTest/QTest>
#include <QTextStream>
#include <QDebug>
#include <QFile>

namespace
{
const QString TEST_FILE_PATH = "dut_file.txt";
constexpr int LINE_NUMBER_0 = 0;
constexpr int LINE_NUMBER_1 = 1;
constexpr int LINE_NUMBER_1500 = 1500;

constexpr int LOG_PORTION_SIZE = 1310;
constexpr int LOG_PORTION_EMPTY = 0;

constexpr int ONE_SIGNAL_EMITED = 1;
constexpr int TWO_SIGNAL_EMITED = 2;
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

    bool result = isEqual(sendDataSpy.count(), ONE_SIGNAL_EMITED);
    LogData data = qvariant_cast<LogData>(sendDataSpy.takeFirst().takeFirst());

    result = result && data.logData.empty();

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

    bool resNum = isEqual(sendDataSpy.count(), ONE_SIGNAL_EMITED);
    LogData data = qvariant_cast<LogData>(sendDataSpy.takeFirst().takeFirst());
    bool resSize = isEqual(data.logData.size(), 1);

    cleanUpTestCase();

    return {resNum && resSize, "readFileWith1Line_shouldEmitFilledLogData"};
}

Result FileReaderTestSuite::testCase_readFileWith1500Line_shouldEmitTwoSignals()
{
    initTestCase();
    fillTestFile(LINE_NUMBER_1500);

    qRegisterMetaType<LogData>();
    QSignalSpy sendDataSpy(_dut.get(), SIGNAL(sendReadData(const LogData&)));

    _dut->readFile();

    bool resNum  = isEqual(sendDataSpy.count(), TWO_SIGNAL_EMITED);
    LogData portion1 = qvariant_cast<LogData>(sendDataSpy.takeFirst().takeFirst());
    LogData portion2 = qvariant_cast<LogData>(sendDataSpy.takeLast().takeFirst());
    bool resSize1 = isEqual(portion1.logData.size(),    LOG_PORTION_SIZE);
    bool resSize2 = isNotEqual(portion2.logData.size(), LOG_PORTION_EMPTY);

    cleanUpTestCase();

    return {resNum && resSize1 && resSize2, "readFileWith1500Line_shouldEmitTwoSignals"};
}

void FileReaderTestSuite::fillTestFile(quint64 linesNumber)
{
    if (_dutFile->open(QFile::Append | QFile::Text))
    {
        QTextStream stream(_dutFile);

        for (quint64 i = 1; i <= linesNumber; ++i)
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
bool FileReaderTestSuite::isEqual(T a1, T a2)
{
    return a1 == a2;
}

template<typename T>
bool FileReaderTestSuite::isNotEqual(T a1, T a2)
{
    return !isEqual<T>(a1, a2);
}
