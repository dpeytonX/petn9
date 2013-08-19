#ifndef PET_H
#define PET_H

#include <QObject>

class QString;

class Pet : public QObject
{
    Q_OBJECT

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
    
signals:
    
public slots:
    
private:
    PETS type;
    QString name;
    long creation;
    int health;
};

#endif // PET_H
