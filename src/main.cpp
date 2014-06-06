#include <petn9.h>

#if PETN9_KDE > 0
#include <KDeclarative/QmlObject>
#endif

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <qglobal.h>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QLocale>

#include <pet.h>
#include <spritemodel.h>
#include "manager.h"
#include "appsettings.h"

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
    app->setApplicationDisplayName(app->tr("Pet N9"));
    app->setApplicationVersion(PETN9_VERSION_MAJOR + "." + PETN9_VERSION_MINOR);

#if PETN9_KDE > 0
    KDeclarative::QmlObject* context = new KDeclarative::QmlObject(app.data());
    QQmlEngine* viewer = (context->engine());
#else
    QQmlApplicationEngine* viewer = new QQmlApplicationEngine(app.data());
#endif

    //Startup context
    QTime time = QTime::currentTime(); //initialize random numbers
    qsrand((uint)time.msec());

    Manager* manager = new Manager(viewer);
    AppSettings* appSettings = new AppSettings(viewer);

    //Set context variables
    qmlRegisterType<Pet>("com.blogspot.iamboke", 1,0, "PetModel");
    qmlRegisterType<SpriteModel>("com.blogspot.iamboke", 1,0, "SpriteModel");
    qRegisterMetaType<PetStatus>("PetStatus");

    viewer->rootContext()->setContextProperty("Manager", manager);
    viewer->rootContext()->setContextProperty("AppSettings", appSettings);

    QUrl qurl( QStringLiteral ( "qrc:///qml/qt5/main.qml" ) );
#if PETN9_KDE > 0
    context->createObjectFromSource (qurl, new QQmlContext(viewer));
#else
    viewer->load (qurl );
#endif

    return app->exec();
}
