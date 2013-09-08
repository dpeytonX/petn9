#include <QDebug>
#include <QList>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>
#include <QDateTime>

#include <cmath>

#include "manager.h"
#include "appsettings.h"
#include "databasemanager.h"
#include "models/pet.h"
#include "qtdeclarative-helper/declarativelist.h"

Manager::Manager(QObject *parent) :
    QObject(parent),
    petModels(new QList<Pet*>())
{
    AppSettings settings;
    QString dbPath = settings.getDatabasePath();
    dbManager = new DatabaseManager(dbPath, this);

    bool isOpen = dbManager->open();
    qDebug() << "Manager: opened db " << isOpen;
    if(!isOpen) {
        qDebug() << dbManager->lastError().text();
    }

    init();
}

QString Manager::getWorld() {

    //Random world selection
#ifndef NO_RANDOM_WORLDS
    int selection = qrand();
    if(selection < RAND_MAX / 3) {
        return "MountainRange";
    } else if(selection < RAND_MAX / 3 * 2)  {
        return "Desert";
    } else {
        return "Plain";
    }
#else
    return "Desert";
#endif

}

void Manager::saveOnExit()
{
    qDebug() << "Manager: Saving...";
}

void Manager::init() {
    createPetModels();
    if(petModels->size()) {
        updateStatus();
    }
}

void Manager::updateStatus() {
    qDebug() << "Manager: updating status";
    //SQLite stores timestamps in UTC
    long currentTime = QDateTime::currentDateTimeUtc().toTime_t();
    qDebug() << "Manager: current time " << currentTime;

    //Calculate
    long lastPoop = dbManager->getLastPoop(*(getCurrentPet()));
    qDebug() << "Manager: poop time " << lastPoop;
    if(lastPoop && currentTime >= lastPoop) {
        //Create sprites if it's been a long time
        int spritesToCreate = (currentTime - lastPoop) / 17280;
        qDebug() << "Manager: spriteToCreate " << spritesToCreate;

        DeclarativeList<SpriteModel>* spriteList = dynamic_cast<DeclarativeList<SpriteModel>*>(getSpriteModels().object);
        int spriteCount = spriteList->getList().size();
        int diff = 5 - spriteCount;
        spritesToCreate = diff <= 0 ? 0 : (int) fmin(spritesToCreate, diff);
        qDebug() << "Manager: spriteToCreate " << spritesToCreate;
        while(spritesToCreate--) {
            qDebug() << "Manager: creating poop spritemodel";
            createSprite(SpriteModel::POOP, -1, -1);
        }
        updateLastPoop();
    }
}

void Manager::createPetModels() {
    QSqlQuery petsQuery = dbManager->getPets();
    QSqlRecord rec = petsQuery.record();
    int idCol = rec.indexOf("PET_ID");
    int typeIdCol = rec.indexOf("TYPE_ID");
    int nameCol = rec.indexOf("NAME");
    int creationCol = rec.indexOf("CREATION");

    while(petsQuery.next()) {
        qDebug() << "Manager: creating pet ";
        int typeId = petsQuery.value(typeIdCol).toInt();
        QString name = petsQuery.value(nameCol).toString();
        long creation = petsQuery.value(creationCol).toLongLong();
        int id = petsQuery.value(idCol).toInt();
        Pet* pet = new Pet();
        switch(typeId) {
        case 0:
            pet->setType(Pet::PET1);
            break;
        case 1:
            pet->setType(Pet::PET2);
            break;
        case 2:
            pet->setType(Pet::PET3);
            break;
        case 3:
            pet->setType(Pet::PET4);
            break;
        default:
            pet->setType(Pet::PET1);
            break;
        }

        pet->setId(id);
        pet->setName(name);
        pet->setCreationTime(creation);
        qDebug() << "Manager: pet " << name << " was created";
        petModels->append(pet);
    }
}

Manager::~Manager() {
    if(!petModels->isEmpty()) {
        foreach(Pet* item, *petModels) {
            if(item) {
                delete item;
            }
        }
    }
    delete petModels;
}

void Manager::updateFed() {
    dbManager->updateLastFedTimestamp(*(getCurrentPet()));
}

void Manager::updateLastPoop() {
    dbManager->updateLastPoopTimestamp(*(getCurrentPet()));
}

void Manager::updateLastAppStart() {
    dbManager->updateLastAppStartTimestamp(*(getCurrentPet()));
}

QDeclarativeListProperty<Pet> Manager::getPetModels() {
    petDeclarativeListHolder = new Pet(this);
    petDeclarativeListHolder->setManageMemory(false);
    foreach(Pet* o, *petModels) {
        petDeclarativeListHolder->getList().append(o);
    }
    return QDeclarativeListProperty<Pet>(petDeclarativeListHolder, 0,
                                         &DeclarativeList<Pet>::appendObject,
                                         &DeclarativeList<Pet>::count,
                                         &DeclarativeList<Pet>::atIndex,
                                         &DeclarativeList<Pet>::clearObject);
}

QDeclarativeListProperty<SpriteModel> Manager::getSpriteModels()
{
    qDebug() << "Manager: retrieving sprite models ";
    spriteDeclarativeListHolder = new SpriteModel(this);
    //Populate Sprite Models
    QSqlQuery spriteQuery = dbManager->getSprites(SpriteModel::ALL);
    QSqlRecord rec = spriteQuery.record();
    int spriteIdCol = rec.indexOf("SPRITE_ID");
    int spriteTypeIdCol = rec.indexOf("SPRITE_TYPE_ID");
    int xCol = rec.indexOf("X");
    int yCol = rec.indexOf("Y");

    while(spriteQuery.next()) {
        qDebug() << "Manager: creating sprite model ";
        int spriteId = spriteQuery.value(spriteIdCol).toInt();
        int spriteTypeId= spriteQuery.value(spriteTypeIdCol).toInt();
        int x = spriteQuery.value(xCol).toInt();
        int y = spriteQuery.value(yCol).toInt();
        SpriteModel* spriteObj = new SpriteModel(this);
        switch(spriteTypeId) {
        case 0:
            spriteObj->setSpriteTypeId(SpriteModel::POOP);
            break;
        case 1:
            spriteObj->setSpriteTypeId(SpriteModel::FOOD);
            break;
        default:
            spriteObj->setSpriteTypeId(SpriteModel::POOP);
            break;
        }

        spriteObj->setId(spriteId);
        spriteObj->setX(x);
        spriteObj->setY(y);
        qDebug() << "Manager: sprite " << spriteId << " was created of type " << spriteTypeId;
        spriteDeclarativeListHolder->getList().append(spriteObj);
    }
    //return QDeclListProp
    return QDeclarativeListProperty<SpriteModel>(spriteDeclarativeListHolder, 0,
                                                 &DeclarativeList<SpriteModel>::appendObject,
                                                 &DeclarativeList<SpriteModel>::count,
                                                 &DeclarativeList<SpriteModel>::atIndex,
                                                 &DeclarativeList<SpriteModel>::clearObject);
}

void Manager::deleteSpriteModel(SpriteModel *spriteToRemove)
{
    qDebug() << "Removing sprite " << spriteToRemove->getId();
    if(spriteToRemove->getSpriteTypeId() == SpriteModel::ALL) {
        qDebug() << "Manager: removing all sprites";
        QDeclarativeListProperty<SpriteModel> spriteProp = getSpriteModels();
        DeclarativeList<SpriteModel>* sprites = dynamic_cast<DeclarativeList<SpriteModel>* >(spriteProp.object);
        foreach(SpriteModel* s,sprites->getList()) {
            qDebug() << "Removing sprite " << s->getId();
            dbManager->deleteSpriteModel(*s);
        }
        return;
    }
    dbManager->deleteSpriteModel(*spriteToRemove);
}

Pet *Manager::createPet(int typeId, const QString& name)
{
    qDebug() << "Manager: creating pet of type: " << typeId;
    Pet* pet = new Pet();
    switch(typeId) {
    case 0:
        pet->setType(Pet::PET1);
        break;
    case 1:
        pet->setType(Pet::PET2);
        break;
    case 2:
        pet->setType(Pet::PET3);
        break;
    case 3:
        pet->setType(Pet::PET4);
        break;
    default:
        pet->setType(Pet::PET1);
        break;
    }

    pet->setName(name);

    bool result = dbManager->insertPetRecord(*pet);
    qDebug() << "Manager: pet created " << result;

    petModels->append(pet);
    emit petAdded();

    return pet;
}

SpriteModel *Manager::createSprite(int spriteTypeId, int x, int y)
{
    qDebug() << "Manager: creating sprite of type: " << spriteTypeId;
    SpriteModel* sprite = new SpriteModel(this);
    switch(spriteTypeId) {
    case 0:
        sprite->setSpriteTypeId(SpriteModel::POOP);
        break;
    case 1:
        sprite->setSpriteTypeId(SpriteModel::FOOD);
        break;
    default:
        sprite->setSpriteTypeId(SpriteModel::POOP);
        break;
    }

    sprite->setX(x);
    sprite->setY(y);

    QSqlQuery spriteQuery = dbManager->insertSpriteRecord(*sprite);
    QSqlRecord rec = spriteQuery.record();
    int spriteIdCol = rec.indexOf("SPRITE_ID");
    while(spriteQuery.next()) {
        qDebug() << "Manager: createSprite retrieved sprite ID ";
        int spriteId = spriteQuery.value(spriteIdCol).toInt();
        sprite->setId(spriteId);
        break;
    }
    qDebug() << "Manager: sprite added to DB ";

    return sprite;
}
