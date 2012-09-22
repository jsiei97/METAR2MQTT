#include <QtCore>
#include <QtTest>

#include <QFile>
#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include "metar.h"

class TestParser : public QObject
{
    Q_OBJECT

    private:
    public:
        bool testParseMETAR(
                QString metarData,
                QString date,
                QString temperature,
                QString dewpoint,
                QString barometricPressure);

        private slots:
            void testParseFile_data();
            void testParseFile();

            void test_MtoInt_data();
            void test_MtoInt();

            void testBadData_data();
            void testBadData();
};


bool TestParser::testParseMETAR(
        QString metarData,
        QString date,
        QString temperature,
        QString dewpoint,
        QString barometricPressure)
{
    /*
       qDebug() << date
       << metarData
       << temperature
       << dewpoint
       << barometricPressure;
       */

    METAR metar;
    metar.init();
    if(!metar.parse(metarData))
    {
        qDebug() << "metar parse failed"
            << date
            << metarData
            << temperature
            << dewpoint
            << barometricPressure;
        return false;
    }

    if( metar.temperature != temperature.toInt())
    {
        qDebug() << "temperature fail"
            << date
            << metarData
            << temperature
            << dewpoint
            << barometricPressure;
        return false;
    }

    if(metar.dewpoint != dewpoint.toInt())
    {
        qDebug() << "dewpoint fail"
            << date
            << metarData
            << temperature
            << dewpoint
            << barometricPressure;
        return false;
    }

    if(metar.barometricPressure != barometricPressure.toInt())
    {
        qDebug() << "barometricPressure fail"
            << date
            << metarData
            << temperature
            << dewpoint
            << barometricPressure;
        return false;
    }

    return true;
}


void TestParser::testParseFile_data()
{
    QTest::addColumn<QString>("metarfile");

    QTest::newRow("mini") << "mini.xml";
    QTest::newRow("EKCH") << "METAR_EKCH.xml";
    QTest::newRow("ESMK") << "METAR_ESMK.xml";
    QTest::newRow("ESMS") << "METAR_ESMS.xml";
}

void TestParser::testParseFile()
{
    QFETCH(QString,metarfile);
    QFile file(metarfile);

    if(!file.exists())
    {
        qDebug() << "Can't find testfile:" << metarfile << file.fileName();
        QFAIL("No file");
    }

    //1. Open file
    //2. every row is a testcase


    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open testfile:" << metarfile << file.fileName();
        QFAIL("Readerror");
    }

    QDomDocument doc("configfile");
    if (!doc.setContent(&file))
    {
        file.close();
        qDebug() << "Can't parse testfile:" << metarfile << file.fileName();
        QFAIL("Parse error");
    }
    file.close();

    QDomElement docElem = doc.documentElement();

    for(QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull())
        {
            //qDebug() << e.tagName();
            if(e.tagName() == "row")
            {
                QDomNodeList tagId = e.elementsByTagName("field");

                /*
                   for(int i=0; i<tagId.count(); i++)
                   {
                   QDomElement tagE = tagId.at(i).toElement();
                   qDebug() << qPrintable(tagE.tagName()) << tagE.text();
                   }
                   */
                QCOMPARE(tagId.count(), 5);

                /*
                   qDebug() << tagId.at(0).toElement().text()
                   << tagId.at(1).toElement().text()
                   << tagId.at(2).toElement().text()
                   << tagId.at(3).toElement().text()
                   << tagId.at(4).toElement().text();
                   */

                // This is the test input for the parser
                // 0 => date
                // 1 => metar code aka input
                // 2 => temperature
                // 3 => dewpoint
                // 4 => airpressure

                QVERIFY(testParseMETAR(
                            tagId.at(1).toElement().text(),
                            tagId.at(0).toElement().text(),
                            tagId.at(2).toElement().text(),
                            tagId.at(3).toElement().text(),
                            tagId.at(4).toElement().text()));


            }

        }
    }


}

void TestParser::test_MtoInt_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<int>("temperature");

    QTest::newRow("Value 14") << "14" << 14;
    QTest::newRow("Value 50") << "50" << 50;
    QTest::newRow("Value 03") << "03" <<  3;

    QTest::newRow("Neg 14") << "M14" << -14;
    QTest::newRow("Neg 50") << "M50" << -50;
    QTest::newRow("Neg 03") << "M03" <<  -3;
}
void TestParser::test_MtoInt()
{
    QFETCH(QString, data);
    QFETCH(int, temperature);

    METAR metar;

    QCOMPARE(temperature, metar.MtoInt(data));

}

void TestParser::testBadData_data()
{
    QTest::addColumn<QString>("data");

    //Make sure he complains about this metars since they are tricky
    QTest::newRow("Faulty METAR 01") << "ESMK 190720Z 25010KT 9999 BKN030 04/02 Q01000";
    QTest::newRow("Faulty METAR 02") << "ESMK 020620Z 27005KT CAVOK 070/M01 Q1032";
    QTest::newRow("Faulty METAR 03") << "ESMS 241350Z 08027G37KT CAVOK 10/01 Q10";
    QTest::newRow("Faulty METAR 04") << "ESMS 091020Z 29020KT 9999 FEW013 SCT015 BKN022 09/07 Q100";
    QTest::newRow("Faulty METAR 05") << "ESMS 110450Z 21010KT 6000 -SHRA SCT005 BKN007 09/09 Q09";
}
void TestParser::testBadData()
{
    QFETCH(QString, data);

    METAR metar;

    metar.init();
    if(metar.parse(data))
    {
        qDebug() << data;
        QFAIL("Error this data is NOT ok, we should not get true back!");
    }

}
QTEST_MAIN(TestParser)
#include "TestParser.moc"
