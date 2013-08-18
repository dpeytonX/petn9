#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

/**
  Manages application settings.
  <p>
  Uses QSettings as a backend to store application-wide settings.
  */
class AppSettings
{
public:
    /**
      Constructs a new QSettings object for storing application configuration data.
      */
    AppSettings();

    /**
      Returns the database path.

      @return the path to the database file.
    */
    QString getDatabasePath();

private:
    QSettings settings;
};

#endif // APPSETTINGS_H
