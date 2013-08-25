#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVariant>
#include <QList>
#include <QDeclarativeListProperty>


#include <cstdlib>


#include "databasemanager.h"
#include "models/pet.h"
#include "models/spritedeclarativelist.h"

/**
  Back-end for QML providing necessary functions for manipulating DTO models and managing the application's database.
  */
class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Pet> pets READ getPetModels)
    Q_PROPERTY(Pet* currentPet READ getCurrentPet)
    Q_PROPERTY(QDeclarativeListProperty<SpriteModel> sprites READ getSpriteModels)
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

    /**
      Returns the pets registered with the application.
      @return a QML accessible list of Pet objects.
      */
    QDeclarativeListProperty<Pet> getPetModels() {
        return QDeclarativeListProperty<Pet>(this, *petModels);
    }

    /**
      Gets the sprite models in use by the game.
      The models returned are not used for persistence so changes will not be saved.
      @return a QML list of SpriteModels
      */
    QDeclarativeListProperty<SpriteModel> getSpriteModels();

    /**
      Returns the pet that the user is interacting with.
      @return the current Pet
      */
    Pet* getCurrentPet() {
        return petModels->empty() ? NULL : petModels->at(petModels->size() - 1);
    }

    /**
      Returns whether this is a simulated environment.
      @return true if this is the NOKIA simulator. False, otherwise.
      */
    Q_INVOKABLE bool isSimulator() {
#if defined(Q_WS_SIMULATOR)
        return true;
#else
        return false;
#endif
    }

    /**
      Returns a string representing the world to create.
      @return a string representation of the world to create.
      */
    Q_INVOKABLE QString getWorld();

    Q_INVOKABLE void saveOnExit();

signals:
    /**
      Emmitted when a Pet is added to the Pet model list.
      */
    void petAdded();

public slots:
    /**
      Creates a new Pet object
      @param is the Pet type. It should match a value in Pet::PETS.
      */
    Pet* createPet(int typeId, const QString &name);

    void createSprite(int spriteTypeId, int x, int y);

private:
    DatabaseManager* dbManager;
    QList<Pet*>* petModels;
    SpriteDeclarativeList* spriteDeclarativeListHolder;

    void createPetModels();
};

Q_DECLARE_METATYPE( Pet* )

#endif // MANAGER_H
