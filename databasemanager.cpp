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

bool DatabaseManager::insertSpriteRecord(const SpriteModel &spriteModel)
{
    QSqlQuery query;
    query.prepare("INSERT Into Sprite (SPRITE_TYPE_ID, X, Y) VALUES(?,?,?)");
    query.addBindValue(spriteModel.getSpriteTypeId());
    query.addBindValue(spriteModel.getX());
    query.addBindValue(spriteModel.getY());
    return query.exec();
}

DatabaseManager::~DatabaseManager() {
}
