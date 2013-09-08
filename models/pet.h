#ifndef PET_H
#define PET_H

#include <QObject>
#include "qtdeclarative-helper/declarativelist.h"

class QString;

struct PetStatus {
    bool isHungry;
    bool isDead;
    bool isSad;

    PetStatus() : isHungry(false), isDead(false), isSad(false) {}
};

/**
  Represents a Pet object.
  */
class Pet : public QObject, public DeclarativeList<Pet>
{
    Q_OBJECT
    Q_ENUMS(PETS)
    Q_PROPERTY(PETS type READ getType)
    Q_PROPERTY(bool dead READ isDead NOTIFY deadChanged)
    Q_PROPERTY(bool hungry READ isHungry NOTIFY hungryChanged)
    Q_PROPERTY(bool sad READ isSad NOTIFY sadChanged)

public:

    enum PETS {PET1, PET2, PET3, PET4};

    explicit Pet(QObject *parent = 0);

    void setType(PETS type) {
        this->type = type;
    }

    void setName(const QString & name) {
        this->name = name;
    }

    void setCreationTime(long creation) {
        this->creation = creation;
    }

    void setId(int id) {
        this->id = id;
    }

    PETS getType() const {
        return type;
    }

    QString getName() const {
        return name;
    }

    long getCreationTime() const {
        return creation;
    }

    int getId() const {
        return id;
    }

    bool isDead() const {
        return status.isDead;
    }

    bool isHungry() const {
        return status.isHungry;
    }

    bool isSad() const {
        return status.isSad;
    }

    void setStatus(PetStatus status) {
        PetStatus prevStat = this->status;
        this->status = status;
        if(prevStat.isDead != status.isDead) {
            emit deadChanged();
        }
        if(prevStat.isHungry != status.isHungry) {
            emit hungryChanged();
        }
        if(prevStat.isSad != status.isSad) {
            emit sadChanged();
        }
    }

signals:
    void deadChanged();
    void hungryChanged();
    void sadChanged();

public slots:

private:
    int id;
    PETS type;
    QString name;
    long creation;
    PetStatus status;
};

#endif // PET_H
