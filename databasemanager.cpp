#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#ifdef NEW_DB
#include <QFile>
#include <QDir>
#endif

DatabaseManager::DatabaseManager(const QString &dbPath, QObject *parent) :
    QObject(parent),
    dbPath(dbPath)
{
}

bool DatabaseManager::open()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
#ifdef NEW_DB
    QDir dir;
    QString dbFile = dir.absolutePath() + dir.separator() + dbPath;
    qDebug() << "DatabaseManager: removing file " << dbFile;
    QFile::remove(dbFile);
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

QSqlQuery DatabaseManager::getPets() {
    QSqlQuery petsQuery("SELECT * FROM Pet");

    return petsQuery;
}

bool DatabaseManager::insertPetRecord(const Pet &pet)
{
    QSqlQuery query;
    query.prepare("INSERT Into Pet (TYPE_ID, NAME, HEALTH) VALUES(?,?,?)");
    query.addBindValue(pet.getType());
    query.addBindValue(pet.getName());
    query.addBindValue(pet.getHealth());
    return query.exec();
}

DatabaseManager::~DatabaseManager() {
}
