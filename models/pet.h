#ifndef PET_H
#define PET_H

#include <QObject>

class Pet : public QObject
{
    Q_OBJECT
public:
    explicit Pet(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PET_H
