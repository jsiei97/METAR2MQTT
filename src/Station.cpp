#include <QString>
#include <QDebug>

#include "Station.h"

Station::Station()
{
    this->name = "";
    this->mosqTopic = "";
}

Station::Station(
        QString name,
        QString mosqTopic)
{
    this->name = name;
    this->mosqTopic = mosqTopic;
}

bool Station::isOK()
{
    if( ( name.size()       > 0 ) &&
        ( mosqTopic.size()  > 0 )
      )
    {
        return true;
    }
    print();
    return false;
}

void Station::print()
{
    qDebug() << "Stationdata"
        << name
        << mosqTopic;
}


void Station::setName( QString name ){
    this->name = name.trimmed();
}
void Station::setMosqTopic( QString mosqTopic ){
    this->mosqTopic = mosqTopic.trimmed();;
}

QString Station::getName(){
    return this->name;
}
QString Station::getMosqTopic(){
    return this->mosqTopic;
}

