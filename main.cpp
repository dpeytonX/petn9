#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>
#include <qglobal.h>
#include <QTime>

#include <cstdlib>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    //Startup context
    QTime time = QTime::currentTime(); //initialize random numbers
    qsrand((uint)time.msec());


    //Set context variables
    int screenWidth = viewer.geometry().width();
    int screenHeight = viewer.geometry().height();
    viewer.rootContext()->setContextProperty("ScreenWidth", screenWidth);
    viewer.rootContext()->setContextProperty("ScreenHeight", screenHeight);

    //Open initial view
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);

    //Random world selection
#ifndef NO_RANDOM_WORLDS
    int selection = qrand();
    if(selection < RAND_MAX / 2) {
        viewer.setMainQmlFile(QLatin1String("qml/petn9/worlds/MountainRange.qml"));
    } else {
        viewer.setMainQmlFile(QLatin1String("qml/petn9/worlds/Plain.qml"));
    }
#else
    viewer.setMainQmlFile(QLatin1String("qml/petn9/worlds/Plain.qml"));
#endif

    viewer.showExpanded();

    return app->exec();
}
