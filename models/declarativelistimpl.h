#ifndef DECLARATIVELISTIMPL_H
#define DECLARATIVELISTIMPL_H

#include <QObject>
#include <QDeclarativeListProperty>
#include <QList>

/**
  QML QDeclarativeListProperty container
  */
template<typename M>
class DeclarativeListImpl
{
public:
    static void appendObject(QDeclarativeListProperty<M> *obj, M *model) {
        DeclarativeListImpl *backEnd = dynamic_cast<DeclarativeListImpl*>(obj->object);
        if(backEnd) {
            backEnd->list.append(model);
        }
    }

    static void clearObject(QDeclarativeListProperty<M> *obj) {
        DeclarativeListImpl* backEnd = dynamic_cast<DeclarativeListImpl*>(obj->object);
        if(backEnd) {
            foreach(M *o, backEnd->list) {
                if(o) {
                    delete o;
                }
            }
            backEnd->list.clear();
        }
    }

    static M* atIndex(QDeclarativeListProperty<M> *obj, int index) {
        DeclarativeListImpl* backEnd = dynamic_cast<DeclarativeListImpl*>(obj->object);
        if(backEnd) {
            return backEnd->list[index];
        }
        return 0;
    }

    static int count(QDeclarativeListProperty<M> *obj) {
        DeclarativeListImpl* backEnd = dynamic_cast<DeclarativeListImpl*>(obj->object);
        if(backEnd) {
            return backEnd->list.size();
        }
        return 0;
    }

    QList<M*> getList() {
        return list;
    }

private:
    QList<M*> list;

};


#endif // DECLARATIVELISTIMPL_H
