#ifndef GLOBALDATASENDER_H
#define GLOBALDATASENDER_H
#include <QNetworkAccessManager>
#include <QString>
class GlobalDataSender
{
public:
    static GlobalDataSender* instance();

    void send(QString data);


private:
    GlobalDataSender();

    static GlobalDataSender* _instance;
    QNetworkAccessManager networkManager;
};

#endif // GLOBALDATASENDER_H
