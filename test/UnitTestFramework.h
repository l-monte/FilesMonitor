#ifndef UNITTESTFRAMEWORK_H
#define UNITTESTFRAMEWORK_H

#include <QDebug>
#include "FileReaderTestSuite.h"

class UnitTestFramework
{
public:
    UnitTestFramework();
    ~UnitTestFramework();

    void runUT()
    {
        run(_readerUT->testCase_readEmptyFile_shouldEmitEmptyLogData());
        run(_readerUT->testCase_readFileWith1Line_shouldEmitFilledLogData());
        run(_readerUT->testCase_readFileWith1500Line_shouldEmitTwoSignals());
    }

    FileReaderTestSuite* _readerUT = new FileReaderTestSuite();

private:
    void run(std::pair<bool, QString> res)
    {
        qDebug() << "Test case: " << res.second << " : " << (res.first ? "PASSED" : "FAILED");
    }
};

#endif // UNITTESTFRAMEWORK_H
