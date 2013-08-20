import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "worlds"

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
        if(!Manager.pets.length) {
            console.log("main.qml: empty pets. Creating first run wizard.")
            appWindow.pageStack.push(Qt.resolvedUrl("FirstRunWizard.qml"), {})
        } else {
            console.log("main.qml: has pets, creating game")
            appWindow.pageStack.push(Qt.resolvedUrl("Game.qml"), {"pet": Manager.pets[0], "world": Manager.getWorld()})
        }
    }

}
