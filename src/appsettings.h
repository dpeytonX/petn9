#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>

class QString;

class AppSettings : public QObject {
    Q_OBJECT

public:
    explicit AppSettings(QObject* parent = 0) : QObject(parent) {}

    Q_INVOKABLE QString locateSharedFile(const QString& fileName);
    Q_INVOKABLE QString locateSoundFile(const QString& fileName);
};

#endif // APPSETTINGS_H
