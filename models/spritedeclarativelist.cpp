#include "spritedeclarativelist.h"

SpriteDeclarativeList::SpriteDeclarativeList(QObject *parent) :
    QObject(parent), listImpl(new DeclarativeListImpl<SpriteDeclarativeList, SpriteModel>())
{
}

SpriteDeclarativeList::~SpriteDeclarativeList() {
    delete listImpl;
}
