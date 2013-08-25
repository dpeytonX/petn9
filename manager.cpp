#include <QDebug>
#include <QList>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>

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

    createPetModels();
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

void Manager::createPetModels() {
    QSqlQuery petsQuery = dbManager->getPets();
    QSqlRecord rec = petsQuery.record();
    int typeIdCol = rec.indexOf("TYPE_ID");
    int nameCol = rec.indexOf("NAME");
    int creationCol = rec.indexOf("CREATION");
    int deadCol = rec.indexOf("IS_DEAD");

    while(petsQuery.next()) {
        qDebug() << "Manager: creating pet ";
        int typeId = petsQuery.value(typeIdCol).toInt();
        QString name = petsQuery.value(nameCol).toString();
        long creation = petsQuery.value(creationCol).toLongLong();
        bool dead = petsQuery.value(deadCol).toBool();
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
        pet->setCreationTime(creation);
        pet->setDead(dead);
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

QDeclarativeListProperty<Pet> Manager::getPetModels() {
    petDeclarativeListHolder = new Pet(this);
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

void Manager::createSprite(int spriteTypeId, int x, int y)
{
    qDebug() << "Manager: creating sprite of type: " << spriteTypeId;
    SpriteModel* sprite = new SpriteModel();
    switch(spriteTypeId) {
    case 0:
        sprite->setSpriteTypeId(SpriteModel::POOP);
        break;
    default:
        sprite->setSpriteTypeId(SpriteModel::POOP);
        break;
    }

    sprite->setX(x);
    sprite->setY(y);

    bool result = dbManager->insertSpriteRecord(*sprite);
    qDebug() << "Manager: sprite added to DB " << result;

    delete sprite;
}
