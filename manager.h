#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVariant>
#include <QList>
#include <QDeclarativeListProperty>


#include <cstdlib>


#include "databasemanager.h"
#include "models/pet.h"

/**
  Back-end for QML providing necessary functions for manipulating DTO models and managing the application's database.
  */
class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Pet> pets READ getPetModels)
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
    Pet* createPet(int typeId);

private:
    DatabaseManager* dbManager;
    QList<Pet*>* petModels;

    void createPetModels();
};

Q_DECLARE_METATYPE( Pet* )

#endif // MANAGER_H
