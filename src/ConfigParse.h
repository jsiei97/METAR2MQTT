#ifndef  __CONFIGPARSE_H
#define  __CONFIGPARSE_H

#include "Station.h"

class ConfigParse 
{
    private: 
        QString configfile;

        QString mqttServer;
        QString mqttAppName;

    public: 
        ConfigParse(QString configfile);
        bool parse(QList<Station> *list);

        QString getMosqServer();
        QString getAppName();
};

#endif  // __CONFIGPARSE_H 
