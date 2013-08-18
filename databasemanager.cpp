#include "databasemanager.h"

DatabaseManager::DatabaseManager(const QString &dbPath) :
    QObject(),
    dbPath(dbPath)
{
}

bool DatabaseManager::open()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    return db.open();
}

QSqlError DatabaseManager::lastError() {
    return db.lastError();
}

void DatabaseManager::close()
{
    db.close();
}


DatabaseManager::~DatabaseManager() {
    close();
}
