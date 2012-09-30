#include "CollectMETAR.h"

#include <QString>

bool CollectMETAR::buildURL(QString station)
{
    if(station.size() != 4)
    {
        //All stations are 4 chars long!
        return false;
    }

    url.clear();
    url.append("http://weather.noaa.gov/pub/data/observations/metar/stations/");
    url.append(station);
    url.append(".TXT");

    return true;
}

QString CollectMETAR::getMetarDataFromServer(QString station)
{
    if(!buildURL(station))
    {
        qDebug() << "Error bad station";
        return "";
    }


    //1. get data
    //2. only save the line that mentions the station name!


    return "";
}

