#ifndef  __STATION_H
#define  __STATION_H


#include <QString>

class Station
{
    private:
        QString name;
        QString mosqTopic;

    public:
        Station();
        Station( QString name,
                QString mosqTopic);

        bool isOK();

        void print();

        void setName( QString name );
        void setMosqTopic( QString mosqTopic );

        QString getName();
        QString getMosqTopic();
};

#endif  // __STATION_H 
