#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVariant>
#include <QList>
#include <QDeclarativeListProperty>


#include <cstdlib>


#include "databasemanager.h"
#include "models/pet.h"


class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Pet> pets READ getPetModels NOTIFY petModelsChanged)
    Q_PROPERTY(QString world READ getWorld)
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();
    DatabaseManager* getDatabaseManager();

    QDeclarativeListProperty<Pet> getPetModels() {
        return QDeclarativeListProperty<Pet>(this, *petModels);
    }

    QString getWorld() {
        //Random world selection
#ifndef NO_RANDOM_WORLDS
        int selection = qrand();
        if(selection < RAND_MAX / 2) {
            return "worlds/MountainRange.qml";
        } else {
            return "worlds/Plain.qml";
        }
#else
        return "worlds/Plain.qml";
#endif
    }
    
signals:
    void petModelsChanged();
    
public slots:
    
private:
    DatabaseManager* dbManager;
    QList<Pet*>* petModels;

    void createPetModels();
};

Q_DECLARE_METATYPE( Pet* )

#endif // MANAGER_H
