#include <QtCore>
#include <QtTest>

#include "ConfigParse.h"
#include "Station.h"

class TestConfig : public QObject
{
    Q_OBJECT

    private:
    public:

    private slots:
        void testParseFile();
};

void TestConfig::testParseFile()
{
    //QCOMPARE(10.0, filter.getValue());

    ConfigParse config("files/config01.xml");
    QList<Station> *list;
    list = new QList<Station>;

    config.parse(list);

    QCOMPARE(config.getMosqServer(), QString("localhost"));
    QCOMPARE(config.getAppName(),    QString("FunTechHouse_METAR2MQTT2__01"));

    QCOMPARE(list->size(), 1);


    {
        Station station = list->at(0);
        QCOMPARE(station.getName(),      QString("EKCH"));
        QCOMPARE(station.getMosqTopic(), QString("METAR/EKCH"));
    }

}

QTEST_MAIN(TestConfig)
#include "TestConfig.moc"
