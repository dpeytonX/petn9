#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QFile>

DatabaseManager::DatabaseManager(const QString &dbPath, QObject *parent) :
    QObject(parent),
    dbPath(dbPath)
{
}

bool DatabaseManager::open()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
#ifdef NEW_DB
    QFile::remove(dbPath);
#endif
    db.setDatabaseName(dbPath);
    bool isDbOpen = db.open();
    QSqlQuery exists("SELECT count(*) AS numTbl FROM sqlite_master WHERE type='table' AND name='Pet'", db);
    if(!exists.exec()) {
        qDebug() << lastError().databaseText();
        return isDbOpen;
    }
    QSqlRecord rec = exists.record();

    int numTbl = rec.indexOf("numTbl");
    if(exists.next() && !exists.value(numTbl).toInt()) {
        qDebug() << "DatabaseManager: no tables exist";
        QFile file(":/petn9/petn9.sql");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while(!file.atEnd()) {
                QString sqlContents = file.readLine();
                qDebug() << "DatabaseManager: contents " << sqlContents;
                QSqlQuery create(sqlContents, db);
                bool createResult = create.exec();
                qDebug() << "DatabaseManager: createResult " << createResult;
                if(!createResult) {
                    qDebug() << lastError().text();
                }
            }
        }
    }

    return isDbOpen;
}

QSqlError DatabaseManager::lastError() {
    return db.lastError();
}

void DatabaseManager::close()
{
    db.close();
}

int DatabaseManager::getPetCount() {
    QSqlQuery petCount("SELECT count(*) AS numPets FROM Pet", db);
    if(!petCount.exec()) {
        qDebug() << "DatabaseManager: getPetCount " << lastError().databaseText();
        return 0;
    }
    QSqlRecord rec = petCount.record();
    int numPets = rec.indexOf("numPets");
    int petCountResult =  (petCount.next() && (petCountResult = petCount.value(numPets).toInt())) ?
                petCountResult : 0;
    qDebug() << "DatabaseManager: getPetCount " << petCountResult;
    return petCountResult;
}

DatabaseManager::~DatabaseManager() {
}
