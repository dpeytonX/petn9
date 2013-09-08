#include "appsettings.h"

#include <QDesktopServices>
#include <QDebug>

AppSettings::AppSettings() :
    settings("iamboke.blogspot.com", "PetN9")
{

}

QString AppSettings::getDatabasePath()
{
    if(settings.contains("database/path")) {
        qDebug() << "AppSettings: " << QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        settings.setValue("database/path", QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/petn9.sqlite");
        return settings.value("database/path", "petn9.sqlite").toString();
    }
    qDebug() << "AppSettings: " << QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    settings.setValue("database/path", QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/petn9.sqlite");
    return getDatabasePath();
}

