#include <QtCore>
#include <QtTest>

#include <QFile>
#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>


class TestParser : public QObject
{
    Q_OBJECT

    private:
    public:

    private slots:
        void testParseFile_data();
        void testParseFile();
};

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
                


            }

        }
    }


}

QTEST_MAIN(TestParser)
#include "TestParser.moc"
