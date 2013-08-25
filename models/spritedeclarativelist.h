#ifndef SPRITEDECLARATIVELIST_H
#define SPRITEDECLARATIVELIST_H

#include <QObject>
#include "declarativelistimpl.h"
#include "spritemodel.h"

class SpriteDeclarativeList : public QObject, public QDeclarativeListProperty<SpriteModel>
{
    Q_OBJECT
public:
    explicit SpriteDeclarativeList(QObject *parent = 0);
    ~SpriteDeclarativeList();

    DeclarativeListImpl<SpriteDeclarativeList, SpriteModel>* getQDeclarativeListImplementation() {
        return listImpl;
    }

    QList<SpriteModel*> getDeclarativeListData() {
        return listImpl->getList();
    }

signals:

public slots:

private:
    DeclarativeListImpl<SpriteDeclarativeList, SpriteModel>* listImpl;
};

#endif // SPRITEDECLARATIVELIST_H
