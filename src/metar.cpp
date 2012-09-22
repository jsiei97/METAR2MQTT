#include <QDebug>
#include <QRegExp>

#include "metar.h"

METAR::METAR()
{
    init();
}
void METAR::init()
{
    temperature = 0;
    dewpoint = 0;
    barometricPressure = 0;
    windSpeed = 0;
    windDirection = 0;
}

/**
 * Convert the metar formatted temperature format int a proper int.
 * Examples 14 is 14, but M14 is -14
 *
 * @param data with a metar formatted temperature value
 * @return temperature in a int
 */
int METAR::MtoInt(QString data)
{
    QRegExp rx("M([0-9]{1,2})");

    if (rx.indexIn(data) != -1)
    {
        QString negData("-");
        negData.append(rx.cap(1));
        data = negData;
    }

    return data.toInt();
}

bool METAR::parse(QString metarData)
{
    //qDebug() << metarData;

    //QRegExp rxMETAR("([A-Z]{4,4}) ([0-9]{6,6}Z).*([0-9A-Z]{5,8}KT).*([M0-9]{2,3})/([M0-9]{2,3}) Q([0-9]{4,4})");
    QRegExp rxMETAR("([A-Z]{4,4}) ([0-9]{6,6}Z).*(M{0,1}[0-9]{1,2})/(M{0,1}[0-9]{1,2}) Q([0-9]{3,4})");

    // Note 1. std tells us QXXXX but sometimes it is only 2-3digits (QXXX)
    // Note 2. std tells us (M)XX/(M)XX but sometimes we get (M)X/(M)X

    if (rxMETAR.indexIn(metarData) != -1)
    {
        /*
           qDebug() << "METAR::parse \n" <<
           "Station    : " << rxMETAR.cap(1) << "\n" <<
           "Date       : " << rxMETAR.cap(2) << "\n" <<
           "Wind       : " << rxMETAR.cap(3) << "\n" <<
           "Temperature: " << rxMETAR.cap(4) << "\n" <<
           "Dewpoint   : " << rxMETAR.cap(5) << "\n" <<
           "BarPressure: " << rxMETAR.cap(6);
           */

        station = rxMETAR.cap(1);

        temperature = MtoInt(rxMETAR.cap(3));
        dewpoint    = MtoInt(rxMETAR.cap(4));

        barometricPressure = rxMETAR.cap(5).toInt();

        //If we accept 3digits we must check for low values
        //But if we only accepted 4digits we will lose some valid data from some stations.
        //For now I will accept 3digits
        if(barometricPressure < 200)
        {
            qDebug() << "Error: To low barometricPressure" << barometricPressure << metarData;
            return false;
        }

        return true;
    }

    qDebug() << metarData;
    return false;
}
