import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.extras 0.1 as PlasmaExtras

import "QmlLogger/qmllogger/Logger.js" as Console

/**
  main.qml

  Contains the page stack and manages common tools
  */
PlasmaExtras.App {
    id: appWindow
    objectName: "appWindow"
    visible: true
    width: Math.min(Screen.desktopAvailableWidth, 800)
    height: Math.min(Screen.desktopAvailableHeight, 600)
    x: (Screen.desktopAvailableWidth - width ) / 2
    y: (Screen.desktopAvailableHeight - height) / 2

    
    property alias pageStack: stackView
    
    StackView {
      id: stackView
      anchors.fill: parent
      
      initialItem: Splash { id: splash }
    }

    Component.onCompleted: {
        Console.LOG_PRIORITY = Console.DEBUG
    }

    Component.onDestruction: {
        Console.critical("main.qml: APP IS CLOSING.")
    }
}
