#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>

#include "models/pet.h"

/**
  Manages database connections for the application.
  */
class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    /**
      Opens a new SQLite Database at the given path.
      <p>
      A new SQLite Database is created if not already existing at path.

      @param dbPath is the path to the DB file
      */
    explicit DatabaseManager(const QString& dbPath, QObject* parent=0);
    ~DatabaseManager();

signals:
    
public slots:

public:
    /**
      Opens a conection to the database.

      @return true if the connection was succesful.
      */
    bool open();
    /**
      Closes a database connection.
      */
    void close();
    /**
      Returns the last given DB error.

      @return the last SQL error.
      */
    QSqlError lastError();

    /**
      Returns the pets created by user.
      @return the query to retrieve the pets.
      */
    QSqlQuery getPets();

    /**
      Inserts a new Pet Model into the database.
      @return true if successful.
      */
    bool insertPetRecord(const Pet& pet);
private:
    QSqlDatabase db;
    QString dbPath;
};

#endif // DATABASEMANAGER_H
