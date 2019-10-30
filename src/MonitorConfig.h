#ifndef MONITORCONFIG_H
#define MONITORCONFIG_H
#include <QString>

constexpr unsigned int ENTRY_PARAM_NUMBER = 3;

constexpr unsigned int SCANNING_TIMER_INTERVAL = 5000;

constexpr unsigned int THREAD_NUMBER = 8;

constexpr unsigned int LOG_LINE_LENGTH = 400;

const QString PEER_ADDR("http://monte.free.beeceptor.com/");


//Logger
constexpr bool WRITE_TO_FILE_FLAG = true;
const QString DEBUG_FILE("../debug.txt");

#endif // MONITORCONFIG_H
