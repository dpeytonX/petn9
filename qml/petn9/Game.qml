import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

import "QmlLogger/qmllogger/Logger.js" as Console

/**
  Game.qml

  Represents the window which contains the environment that the user interacts with.
  */
DefaultPage {
    id: game

    property Pet pet
    property string world
    property variant worldObject

    Component.onCompleted: {
        var component = Qt.createComponent("worlds/" + world + ".qml")
        worldObject = component
        if(component.status == Component.Ready) {
            worldObject = component.createObject(game, {"pet": pet, "anchors.fill": game})
            Console.debug("Game.qml: created world " + worldObject)
        } else if (component.status == Component.Error) {
            // Error Handling
            Console.error("Error loading world:", component.errorString());
        } else {
            Console.debug("Game.qml: world not ready")
            component.statusChanged.connect(finishWorld());
        }
    }

    function finishWorld() {
        Console.debug("Game: finish world")
        if (worldObject.status == Component.Ready) {
            worldObject = component.createObject(game, {"pet": pet, "anchors.fill": game})
            if (worldObject == null) {
                // Error Handling
                Console.error("Error creating world");
            }
        } else if (worldObject.status == Component.Error) {
            // Error Handling
            Console.error("Error loading world:", worldObject.errorString());
        }
    }
}
