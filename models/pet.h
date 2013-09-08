#ifndef PET_H
#define PET_H

#include <QObject>
#include "qtdeclarative-helper/declarativelist.h"

class QString;

struct PetStatus {
    bool isHungry = false;
    bool isDead = true;
    bool isSad = false;
};

/**
  Represents a Pet object.
  */
class Pet : public QObject, public DeclarativeList<Pet>
{
    Q_OBJECT
    Q_ENUMS(PETS)
    Q_PROPERTY(PETS type READ getType)
    Q_PROPERTY(bool dead READ isDead)
    Q_PROPERTY(bool hungry READ isHungry)
    Q_PROPERTY(bool sad READ isSad)

public:

    enum PETS {PET1, PET2, PET3, PET4, DEAD};

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
        this->status = status;
    }

signals:

public slots:

private:
    int id;
    PETS type;
    QString name;
    long creation;
    PetStatus status;
};

#endif // PET_H
