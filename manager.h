#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "databasemanager.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    DatabaseManager* getDatabaseManager();
    
signals:
    
public slots:
    
private:
    DatabaseManager* dbManager;
};

#endif // MANAGER_H
