#include <QObject>
#include <QTest>
#include <appsettings.h>
#include <iostream>

using namespace std;

/**
 * LocateTest
 *
 * This object tests the AppSettings utility to search for resources in the Qt Standard Paths locations.
 */
class LocateTest: public QObject {
    Q_OBJECT
private slots:
    void initTestCase() {
        appSettings = new AppSettings();
    }
    void testShareDirExists() {
        cout << "starting testShareDirExists" << endl;
        QString result = appSettings->locateSoundFile("");
        cout << "result = " << result.toStdString() << endl;
        QVERIFY(result != "");
    }

    void testNotExistantFile() {
        cout << "starting testNonExistantFile" << endl;
        QString result = appSettings->locateSoundFile("asdfaw2feoijaw;lifajaiweof;woifej");
        cout << "result = " << result.toStdString() << endl;
        QVERIFY(result == "");
    }

    void cleanupTestCase() {
        if(appSettings != nullptr)
            delete appSettings;
    }

private:
    AppSettings* appSettings;

};

QTEST_MAIN(LocateTest)
#include <locatetest.moc>
