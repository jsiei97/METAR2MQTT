#ifndef  __COLLECTMETAR_H
#define  __COLLECTMETAR_H

#include <QString>

class CollectMETAR
{
    private:
        QString url;

        bool buildURL(QString station);
    public:
        QString getMetarDataFromServer(QString station);
};

#endif  // __COLLECTMETAR_H
