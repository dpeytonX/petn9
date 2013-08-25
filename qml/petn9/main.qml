import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  main.qml

  Contains the page stack and manages common tools
  */
PageStackWindow {
    id: appWindow
    objectName: "appWindow"
    showStatusBar: false

    initialPage: Page { anchors.fill: parent}

    Component.onCompleted: {
        Console.LOG_PRIORITY = Console.INFO
        if(!Manager.pets.length) {
            Console.info("main.qml: empty pets. Creating first run wizard.")
            appWindow.pageStack.push(Qt.resolvedUrl("FirstRunWizard.qml"), {})
        } else {
            Console.info("main.qml: has pets, creating game")
            appWindow.pageStack.push(Qt.resolvedUrl("Game.qml"))
        }
    }

    Component.onDestruction: {
        Console.critical("main.qml: APP IS CLOSING.")
        Manager.saveOnExit()
    }
}
