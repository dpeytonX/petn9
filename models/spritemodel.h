#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QObject>
#include <QDeclarativeListProperty>
#include <QList>


class SpriteModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(SPRITES)
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(SPRITES typeId READ getSpriteTypeId)
    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
public:
    class SpriteModelListImpl {
    public:
        SpriteModelListImpl() : list(QList<SpriteModel*>()){
        }

        static void appendObject(QDeclarativeListProperty<SpriteModel> *obj, SpriteModel *model) {
            SpriteModel *backEnd = qobject_cast<SpriteModel*>(obj->object);
            if(backEnd) {
                backEnd->models.list.append(model);
            }
        }

        static void clearObject(QDeclarativeListProperty<SpriteModel> *obj) {
            SpriteModel* backEnd = qobject_cast<SpriteModel*>(obj->object);
            if(backEnd) {
                foreach(SpriteModel *o, backEnd->models.list) {
                    delete o;
                }
                backEnd->models.list.clear();
            }
        }

        static SpriteModel* atIndex(QDeclarativeListProperty<SpriteModel> *obj, int index) {
            SpriteModel* backEnd = qobject_cast<SpriteModel*>(obj->object);
            if(backEnd) {
                return backEnd->models.list[index];
            }
            return 0;
        }

        static int count(QDeclarativeListProperty<SpriteModel> *obj) {
            SpriteModel* backEnd = qobject_cast<SpriteModel*>(obj->object);
            if(backEnd) {
                return backEnd->models.list.size();
            }
            return 0;
        }

        friend void appendSpriteModelToInternalList(SpriteModel::SpriteModelListImpl* listImpl, SpriteModel* otherSprite) {
            listImpl->list.append(otherSprite);
        }

    private:
        QList<SpriteModel*> list;
    };


    enum SPRITES {POOP, ALL};
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

    SpriteModelListImpl& getDeclarativeListImpl() {
        return models;
    }

signals:

public slots:

private:
    int id;
    SPRITES type;
    int x;
    int y;
    SpriteModelListImpl models;
};

#endif // SPRITEMODEL_H
