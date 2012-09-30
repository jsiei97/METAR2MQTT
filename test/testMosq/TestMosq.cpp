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
    /// @todo Shall I change the Mosq code into the signal slot model so it becomes testable...


}

QTEST_MAIN(TestMosq)
#include "TestMosq.moc"
