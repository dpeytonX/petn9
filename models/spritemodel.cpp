#include "spritemodel.h"

SpriteModel::SpriteModel(QObject *parent) :
    QObject(parent),DeclarativeList<SpriteModel>(), id(-1), type(SpriteModel::ALL), x(0), y(0)
{
}
