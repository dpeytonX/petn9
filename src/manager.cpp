#include <QDebug>
#include <QList>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>

#include <cmath>

#include <petn9.h>
#include "manager.h"
#include "databasemanager.h"
#include <pet.h>
#include <declarativelist.h>

Manager::Manager(QObject* parent) :
    QObject(parent),
    petModels(new QList<Pet*>()) {
    QString storagePath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    qDebug() << "Standard Path: " << storagePath;
    QDir().mkpath(storagePath);
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/petn9.sqlite";
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
#if RANDOM_WORLDS > 0
    qDebug() << "No random worlds";
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

void Manager::reset() {
    qDebug() << "Manager: Reset...";
    SpriteModel* s = new SpriteModel(this);
    s->setSpriteTypeId(SpriteModel::ALL);
    deleteSpriteModel(s);
    removePet();

}

void Manager::init() {
    createPetModels();
    if(petModels->size()) {
        initPoopModels();
        updateStatus();
    }
}

void Manager::updateStatus() {
    qDebug() << "Manager: updating status";
    Pet* pet = getCurrentPet();
    PetStatus status;
    long currentTime = QDateTime::currentDateTimeUtc().toTime_t();
    qDebug() << "Manager: current time " << currentTime;
    long foodTime = dbManager->getLastFedTimestamp(*pet);
    qDebug() << "Manager: food time " << foodTime;
    if(foodTime && currentTime >= foodTime) {
        long diff = currentTime - foodTime;
        bool hungry = diff >= (60 * 60 * 24 * 2 / 3);
        qDebug() << "Manager: pet is" << (hungry ? "" : "not") << "hungry";
        status.isHungry = hungry;
        bool dead = diff >= 60 * 60 * 24 * 7;
        qDebug() << "Manager: pet is" << (dead ? "" : "not") << "dead";
        status.isDead = dead;
    }
    long lastAppStart = dbManager->getLastAppStart(*pet);
    qDebug() << "Manager: last app start " << lastAppStart;
    if(lastAppStart && currentTime >= lastAppStart) {
        long diff = currentTime - lastAppStart;
        bool sad = diff >= 60 * 60 * 24 * 4;
        qDebug() << "Manager: pet is" << (sad ? "" : "not") << "sad";
        status.isSad = sad;
    }

    pet->setStatus(status);
}

void Manager::initPoopModels() {
    qDebug() << "Manager: initializing poop sprites";
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

void Manager::removePet() {
    Pet* pet = getCurrentPet();
    dbManager->deletePetRecord(*pet);
    int i = petModels->indexOf(pet);
    if(i != -1) {
        petModels->removeAt(i);
        delete pet;
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

QQmlListProperty<Pet> Manager::getPetModels() {
    petQQmlListPropertyHolder = new Pet(this);
    petQQmlListPropertyHolder->setManageMemory(false);
    foreach(Pet* o, *petModels) {
        petQQmlListPropertyHolder->getList().append(o);
    }
    return QQmlListProperty<Pet>(petQQmlListPropertyHolder, 0,
                                 &DeclarativeList<Pet>::appendObject,
                                 &DeclarativeList<Pet>::count,
                                 &DeclarativeList<Pet>::atIndex,
                                 &DeclarativeList<Pet>::clearObject);
}

QQmlListProperty<SpriteModel> Manager::getSpriteModels() {
    qDebug() << "Manager: retrieving sprite models ";
    spriteQQmlListPropertyHolder = new SpriteModel(this);
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
        spriteQQmlListPropertyHolder->getList().append(spriteObj);
    }
    //return QDeclListProp
    return QQmlListProperty<SpriteModel>(spriteQQmlListPropertyHolder, 0,
                                         &DeclarativeList<SpriteModel>::appendObject,
                                         &DeclarativeList<SpriteModel>::count,
                                         &DeclarativeList<SpriteModel>::atIndex,
                                         &DeclarativeList<SpriteModel>::clearObject);
}

void Manager::deleteSpriteModel(SpriteModel* spriteToRemove) {
    qDebug() << "Removing sprite " << spriteToRemove->getId();
    if(spriteToRemove->getSpriteTypeId() == SpriteModel::ALL) {
        qDebug() << "Manager: removing all sprites";
        QQmlListProperty<SpriteModel> spriteProp = getSpriteModels();
        DeclarativeList<SpriteModel>* sprites = dynamic_cast<DeclarativeList<SpriteModel>* >(spriteProp.object);
        foreach(SpriteModel* s,sprites->getList()) {
            qDebug() << "Removing sprite " << s->getId();
            dbManager->deleteSpriteModel(*s);
        }
        return;
    }
    dbManager->deleteSpriteModel(*spriteToRemove);
}

Pet* Manager::createPet(int typeId, const QString& name) {
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

SpriteModel* Manager::createSprite(int spriteTypeId, int x, int y) {
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
