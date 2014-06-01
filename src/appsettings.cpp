#include "appsettings.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QStringList>

QString AppSettings::locateSharedFile(const QString& fileName) {
    QStringList dataLocations = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    
    for(int i = 0; i < dataLocations.size(); i++) {
        QString testFile = dataLocations.at(i) + QDir::separator() + fileName;
        qDebug() << "Testing file location " << i << ": " << testFile;
        
        if(QFile(testFile).exists()) {
            return testFile;
        }
    }
    
    //CMAKE Build Location
    //QString testFile = QCoreApplication::applicationDirPath() + "/../resources/" + fileName;
    QString testFile = "/home/dametrious/Projects/qt/petn9/resources/" + fileName;
    qDebug() << "testing build path: " << testFile;
    if(QFile(testFile).exists()) {
        return testFile;
    }
    
    qDebug() << "file not found: " << fileName;
    return "";
}

QString AppSettings::locateSoundFile(const QString& fileName) {
    return locateSharedFile(QString("sounds") + QDir::separator() + fileName);
}