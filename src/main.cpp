#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <qglobal.h>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QLocale>

#include <petn9.h>
#include <pet.h>
#include "manager.h"
#include <spritemodel.h>

Q_DECL_EXPORT int main(int argc, char* argv[]) {
    QScopedPointer<QGuiApplication> app(new QGuiApplication ( argc, argv ));
    QTranslator translator;

#if ALLOW_JP > 0
    qDebug() << "Loading Japanese translation";
    if(!translator.load("tr_jp", ":/translations")) {
        qDebug() << "Could not load Japanese translation";
    }
#else
    QString locale = QLocale::system().name();
    qDebug() << "Loading translations for " << locale;
    if(!(translator.load("tr_"+locale, ":/translations"))) {
        qDebug() << "Could not find translation for " << locale;
        translator.load("tr_en", ":/translations");
    }
#endif
    app->installTranslator(&translator);


    QQmlApplicationEngine viewer;
    //Startup context
    QTime time = QTime::currentTime(); //initialize random numbers
    qsrand((uint)time.msec());

    Manager* manager = new Manager(&viewer);

    //Set context variables
    qmlRegisterType<Pet>("com.blogspot.iamboke", 1,0, "PetModel");
    qmlRegisterType<SpriteModel>("com.blogspot.iamboke", 1,0, "SpriteModel");
    qRegisterMetaType<PetStatus>("PetStatus");

    viewer.rootContext()->setContextProperty("Manager", manager);

    viewer.load ( QUrl ( QStringLiteral ( "qrc:///qml/petn9/main.qml" ) ) );

    return app->exec();
}
