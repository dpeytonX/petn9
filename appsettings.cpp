#include "appsettings.h"

AppSettings::AppSettings() :
    settings("iamboke.blogspot.com", "PetN9")
{

}

QString AppSettings::getDatabasePath()
{
    if(settings.contains("database/path")) {
        return settings.value("database/path", "petn9.sqlite").toString();
    }
    settings.setValue("database/path", "petn9.sqlite");
    return getDatabasePath();
}

