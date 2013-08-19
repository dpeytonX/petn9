#include <QDebug>

#include "manager.h"
#include "appsettings.h"
#include "databasemanager.h"

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    AppSettings settings;
    QString dbPath = settings.getDatabasePath();
    dbManager = new DatabaseManager(dbPath, this);

    bool isOpen = dbManager->open();
    qDebug() << "main: opened db " << isOpen;
    if(!isOpen) {
        qDebug() << dbManager->lastError().text();
    }
}

DatabaseManager* Manager::getDatabaseManager() {
    return dbManager;
}
