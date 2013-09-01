#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QObject>
#include "qtdeclarative-helper/declarativelist.h"

/**
  Represents the extra models that are added to the game.
  */
class SpriteModel : public QObject, public DeclarativeList<SpriteModel>
{
    Q_OBJECT
    Q_ENUMS(SPRITES)
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(SPRITES typeId READ getSpriteTypeId WRITE setSpriteTypeId)
    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
public:
    /** Sprite Models For the Game **/
    enum SPRITES {POOP, FOOD, OTHER, ALL};
    explicit SpriteModel(QObject *parent = 0);

    SPRITES getSpriteTypeId() const {
        return type;
    }

    int getId() const {
        return id;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setSpriteTypeId(SPRITES type) {
        this->type = type;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    void setId(int id) {
        this->id = id;
    }

signals:

public slots:

private:
    int id;
    SPRITES type;
    int x;
    int y;
};

#endif // SPRITEMODEL_H
