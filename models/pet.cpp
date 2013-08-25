#include "pet.h"

Pet::Pet(QObject *parent) :
    QObject(parent),DeclarativeList<Pet>(), dead(false)
{
}
