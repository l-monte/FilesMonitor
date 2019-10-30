#ifndef FILEREADERTESTSUITE_H
#define FILEREADERTESTSUITE_H

#include <QObject>
#include <memory>
#include "../src/FileReader.h"
#include "../src/MonitorDefs.h"

using Result = std::pair<bool, QString>;

class QFile;

class FileReaderTestSuite : public QObject
{
    Q_OBJECT
public:
    explicit FileReaderTestSuite(QObject *parent = nullptr);

    Result testCase_readEmptyFile_shouldEmitEmptyLogData();
    Result testCase_readFileWith1Line_shouldEmitFilledLogData();
    Result testCase_readFileWith1500Line_shouldEmitTwoSignals();

private:
    void initTestCase();
    void cleanUpTestCase();

    // helpers methods
    void fillTestFile(quint64 linesNumber);

    template<typename T>
    bool isEqual(T a1, T a2);

    template<typename T>
    bool isNotEqual(T a1, T a2);

private:
    std::unique_ptr<FileReader> _dut;

    QFile* _dutFile;
};

Q_DECLARE_METATYPE(LogData)

#endif // FILEREADERTESTSUITE_H
