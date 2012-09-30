#include <QtCore>
#include <QtTest>


class TestMosq : public QObject
{
    Q_OBJECT

    private:
    public:

    private slots:
        void testMosqPub();
};

void TestMosq::testMosqPub()
{
    


}

QTEST_MAIN(TestMosq)
#include "TestMosq.moc"
