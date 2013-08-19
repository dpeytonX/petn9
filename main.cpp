#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>
#include <qglobal.h>
#include <QTime>
#include <QDebug>
#include <QString>

#include <cstdlib>

#include "manager.h"

void initWorld(QmlApplicationViewer & viewer);

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    //Startup context
    QTime time = QTime::currentTime(); //initialize random numbers
    qsrand((uint)time.msec());

    Manager* manager = new Manager(&viewer);

    bool isFirstRun = !manager->getDatabaseManager()->getPetCount();
    qDebug() << "main: first run " << isFirstRun;

    //Set context variables
    int screenWidth = viewer.geometry().width();
    int screenHeight = viewer.geometry().height();
    viewer.rootContext()->setContextProperty("ScreenWidth", screenWidth);
    viewer.rootContext()->setContextProperty("ScreenHeight", screenHeight);
    viewer.rootContext()->setContextProperty("Manager", manager);

    //Open initial view
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);

    //TODO: move UI selection to QML
    if(isFirstRun) {
        viewer.setMainQmlFile(QLatin1String("qml/petn9/FirstRunWizard.qml"));
    } else {
        initWorld(viewer);
    }

    viewer.showExpanded();

    return app->exec();
}

void initWorld(QmlApplicationViewer & viewer) {
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
}
