#ifndef PET_H
#define PET_H

#include <QObject>

class QString;

/**
  Represents a Pet object.
  */
class Pet : public QObject
{
    Q_OBJECT
    Q_ENUMS(PETS)
    Q_PROPERTY(PETS type READ getType)
    Q_PROPERTY(bool dead READ isDead)

public:
    enum PETS {PET1, PET2, PET3, PET4, DEAD};

    explicit Pet(QObject *parent = 0);

    void setDead(bool dead) {
        this->dead = dead;
    }

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
        return dead;
    }

signals:

public slots:

private:
    int id;
    PETS type;
    QString name;
    long creation;
    bool dead;
};

#endif // PET_H
