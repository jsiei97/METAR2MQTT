#include <QtCore>
#include <QtTest>

#include "CollectMETAR.h"

class TestCollect : public QObject
{
    Q_OBJECT

    private:
    public:

    private slots:
        void testBuildURL();
        void testBuildURL_data();
};

void TestCollect::testBuildURL_data()
{
    QTest::addColumn<QString>("station");
    QTest::addColumn<QString>("url");

    QTest::newRow("EKCH") 
        << "EKCH" 
        << "http://weather.noaa.gov/pub/data/observations/metar/stations/EKCH.TXT";


    QTest::newRow("ESMS") 
        << "ESMS"
        << "http://weather.noaa.gov/pub/data/observations/metar/stations/ESMS.TXT";

    QTest::newRow("ESMK") 
        << "ESMK"
        << "http://weather.noaa.gov/pub/data/observations/metar/stations/ESMK.TXT";
}

void TestCollect::testBuildURL()
{
    QFETCH(QString,station);
    QFETCH(QString,url);

    //qDebug() << url << station;

    CollectMETAR collect;

    QVERIFY(collect.buildURL(station));

    QCOMPARE(url, collect.url);
}

QTEST_MAIN(TestCollect)
#include "TestCollect.moc"
