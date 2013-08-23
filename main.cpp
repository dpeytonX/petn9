#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>
#include <qglobal.h>
#include <QTime>
#include <QDebug>
#include <QString>

#include "manager.h"
#include "models/pet.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    //Startup context
    QTime time = QTime::currentTime(); //initialize random numbers
    qsrand((uint)time.msec());

    Manager* manager = new Manager(&viewer);

    //Set context variables
    qmlRegisterType<Pet>("com.blogspot.iamboke", 1,0, "Pet");

    int screenWidth = viewer.geometry().width();
    int screenHeight = viewer.geometry().height();
    qDebug() << "main.cpp: dimensions (" << screenWidth << "," << screenHeight << ")";
    viewer.rootContext()->setContextProperty("ScreenWidth", screenWidth);
    viewer.rootContext()->setContextProperty("ScreenHeight", screenHeight);
    viewer.rootContext()->setContextProperty("Manager", manager);

    //Open initial view
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);

    viewer.setMainQmlFile(QLatin1String("qml/petn9/main.qml"));

    viewer.showExpanded();

    return app->exec();
}
