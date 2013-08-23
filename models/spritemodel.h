#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QObject>

class SpriteModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(SPRITES)
public:
    enum SPRITES {POOP};
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
signals:
    
public slots:
    
private:
    int id;
    SPRITES type;
    int x;
    int y;
};

#endif // SPRITEMODEL_H
