#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDateTime>

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

QSqlQuery DatabaseManager::getSprites(SpriteModel::SPRITES typeId) {
    QSqlQuery spriteQuery;
    if(typeId == SpriteModel::ALL) {
        spriteQuery.prepare("SELECT * FROM Sprite");
        spriteQuery.exec();
        return spriteQuery;
    }
    spriteQuery.prepare("SELECT * FROM Sprite WHERE SPRITE_TYPE_ID = ?");
    spriteQuery.addBindValue(typeId);
    spriteQuery.exec();
    return spriteQuery;
}

bool DatabaseManager::insertPetRecord(const Pet &pet)
{
    QSqlQuery query;
    query.prepare("INSERT Into Pet (TYPE_ID, NAME, IS_DEAD) VALUES(?,?,?)");
    query.addBindValue(pet.getType());
    query.addBindValue(pet.getName());
    query.addBindValue(pet.isDead());
    return query.exec();
}

QSqlQuery DatabaseManager::insertSpriteRecord(const SpriteModel &spriteModel)
{
    QSqlQuery query;
    query.prepare("INSERT Into Sprite (SPRITE_TYPE_ID, X, Y) VALUES(?,?,?)");
    query.addBindValue(spriteModel.getSpriteTypeId());
    query.addBindValue(spriteModel.getX());
    query.addBindValue(spriteModel.getY());
    query.exec();
    QSqlQuery query2;
    query2.prepare("SELECT * FROM Sprite ORDER BY SPRITE_ID DESC");
    query2.exec();
    return query2;
}

bool DatabaseManager::deleteSpriteModel(const SpriteModel &spriteModel)
{
    qDebug() << "DatabaseManager: deleting sprite model " << spriteModel.getId();
    QSqlQuery query;
    query.prepare("DELETE FROM Sprite WHERE SPRITE_ID = ?");
    query.addBindValue(spriteModel.getId());
    return query.exec();
}

DatabaseManager::~DatabaseManager() {
}

void DatabaseManager::updateLastFedTimestamp(const Pet &pet)
{
    initStatus(pet.getId());
    qDebug() << "DatabaseManager: update LAST_FED timestamp";
    QSqlQuery query;
    query.prepare("UPDATE Status SET LAST_FED=CURRENT_TIMESTAMP WHERE PET_ID=?");
    query.addBindValue(pet.getId());
    query.exec();
}

void DatabaseManager::updateLastPoopTimestamp(const Pet &pet)
{
    initStatus(pet.getId());
    qDebug() << "DatabaseManager: update LAST_POOP timestamp";
    QSqlQuery query;
    query.prepare("UPDATE Status SET LAST_POOP=CURRENT_TIMESTAMP WHERE PET_ID=?");
    query.addBindValue(pet.getId());
    query.exec();
}

void DatabaseManager::updateLastAppStartTimestamp(const Pet &pet)
{
    initStatus(pet.getId());
    qDebug() << "DatabaseManager: update LAST_APP_START timestamp";
    QSqlQuery query;
    query.prepare("UPDATE Status SET LAST_APP_START=CURRENT_TIMESTAMP WHERE PET_ID=?");
    query.addBindValue(pet.getId());
    query.exec();
}

long DatabaseManager::getLastFedTimestamp(const Pet &pet) {
    QSqlQuery query = getStatus(pet);
    QSqlRecord rec = query.record();
    int statCol = rec.indexOf("LAST_FED");

    while(query.next()) {
        qDebug() << "Manager: creating sprite model ";
        return query.value(statCol).toLongLong();
    }
    return 0;
}

long DatabaseManager::getLastPoop(const Pet &pet)
{
    QSqlQuery query = getStatus(pet);
    QSqlRecord rec = query.record();
    int statCol = rec.indexOf("LAST_POOP");

    while(query.next()) {
        qDebug() << "DatabaseManager: creating sprite model ";
        QString result = query.value(statCol).toString();
        qDebug() << "DatabaseManager: time result " << result;
        QDateTime time = QDateTime::fromString(result, "yyyy-MM-dd hh:mm:ss");
        qDebug() << "DatabaseManager: DateTimeConversion " << time.toString();
        return time.toTime_t();
    }
    return 0;
}

long DatabaseManager::getLastAppStart(const Pet &pet)
{
    QSqlQuery query = getStatus(pet);
    QSqlRecord rec = query.record();
    int statCol = rec.indexOf("LAST_APP_START");

    while(query.next()) {
        qDebug() << "Manager: creating sprite model ";
        return query.value(statCol).toLongLong();
    }
    return 0;
}

void DatabaseManager::initStatus(int petId) {
    //Initialize Status table
    qDebug() << "DatabaseManager: initializing status table ";
    QSqlQuery query;
    query.prepare("INSERT INTO Status (PET_ID) VALUES(?);");
    query.addBindValue(petId);
    query.exec();
}

QSqlQuery DatabaseManager::getStatus(const Pet &pet)
{
    qDebug() << "DatabaseManager: getting status";
    QSqlQuery query;
    query.prepare("SELECT * FROM Status WHERE PET_ID = ?");
    query.addBindValue(pet.getId());
    query.exec();
    return query;
}
