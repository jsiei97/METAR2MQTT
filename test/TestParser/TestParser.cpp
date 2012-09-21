#include <QtCore>
#include <QtTest>


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
    }

    //1. Open file
    //2. every row is a testcase


}

QTEST_MAIN(TestParser)
#include "TestParser.moc"
