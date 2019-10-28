#include "UnitTestFramework.h"

UnitTestFramework::UnitTestFramework()
{

}

UnitTestFramework::~UnitTestFramework()
{
    if (not _readerUT)
        delete _readerUT;
}
