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

    void setHealth(int health) {
        this->health = health;
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

    int getHealth() const {
        return health;
    }
    
    int getId() const {
        return id;
    }
    
signals:
    
public slots:
    
private:
    int id;
    PETS type;
    QString name;
    long creation;
    int health;
};

#endif // PET_H
