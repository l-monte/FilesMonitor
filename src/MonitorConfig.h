#ifndef MONITORCONFIG_H
#define MONITORCONFIG_H
#include <QString>

constexpr unsigned int ENTRY_PARAM_NUMBER = 2;

constexpr unsigned int THREAD_NUMBER = 8;

const QString PEER_ADDR("http://monte.free.beeceptor.com/");

constexpr unsigned int LOG_LINE_LENGTH = 400;

// 2 MB -> 2097152 B -> 2 097 152 / (400 chars * 4B) ~ 1310
constexpr unsigned int LINE_NUMBER_IN_ONE_LOG_CHUNK = 1310;

//Logger
constexpr bool WRITE_TO_FILE_FLAG = true;
const QString DEBUG_FILE("../debug.txt");

// Unit tests
constexpr bool IS_UNIT_TEST_MODE = true;


//Logger
constexpr bool WRITE_TO_FILE_FLAG = true;
const QString DEBUG_FILE("../debug.txt");

#endif // MONITORCONFIG_H
