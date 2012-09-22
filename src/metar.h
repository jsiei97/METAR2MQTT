#ifndef  __METAR_H
#define  __METAR_H

#include <QString>

class METAR
{
    private:
        QString station;
        int temperature;        ///< Temperature in deg C
        int dewpoint;           ///< Dew point in deg C
        int barometricPressure; ///< Barometric pressure in hPa
        int windSpeed;
        int windDirection;

        int MtoInt(QString data);

    public:
        METAR();
        void init();
        bool parse(QString metarData);

};

#endif  // __METAR_H
