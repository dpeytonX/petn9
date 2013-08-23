#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QObject>

class SpriteModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(SPRITES)
public:
    enum SPRITES {POOP, ALL};
    explicit SpriteModel(QObject *parent = 0);
    
    SPRITES getSpriteTypeId() const {
        return type;
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

signals:
    
public slots:
    
private:
    int id;
    SPRITES type;
    int x;
    int y;
};

#endif // SPRITEMODEL_H
