#ifndef DATASENDER_H
#define DATASENDER_H
#include <QString>

class DataSender
{
public:
    DataSender();

    void send();

private:
    QString _ipAddr;        // TODO: refactor me to IPAddr type
    unsigned int _port;
};

#endif // DATASENDER_H
