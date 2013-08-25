#ifndef DECLARATIVELISTIMPL_H
#define DECLARATIVELISTIMPL_H

#include <QObject>
#include <QDeclarativeListProperty>
#include <QList>

/**
  QML QDeclarativeListProperty container
  */
template<typename Wrapper, typename M>
class DeclarativeListImpl
{
public:
    static void appendObject(QDeclarativeListProperty<M> *obj, M *model) {
        Wrapper *backEnd = qobject_cast<Wrapper*>(obj->object);
        if(backEnd) {
            backEnd->getQDeclarativeListImplementation()->list.append(model);
        }
    }

    static void clearObject(QDeclarativeListProperty<M> *obj) {
        Wrapper* backEnd = qobject_cast<Wrapper*>(obj->object);
        if(backEnd) {
            foreach(M *o, backEnd->getQDeclarativeListImplementation()->list) {
                delete o;
            }
            backEnd->getQDeclarativeListImplementation()->list.clear();
        }
    }

    static M* atIndex(QDeclarativeListProperty<M> *obj, int index) {
        Wrapper* backEnd = qobject_cast<Wrapper*>(obj->object);
        if(backEnd) {
            return backEnd->getQDeclarativeListImplementation()->list[index];
        }
        return 0;
    }

    static int count(QDeclarativeListProperty<M> *obj) {
        Wrapper* backEnd = qobject_cast<Wrapper*>(obj->object);
        if(backEnd) {
            return backEnd->getQDeclarativeListImplementation()->list.size();
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
