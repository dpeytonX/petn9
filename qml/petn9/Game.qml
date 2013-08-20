import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

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
            console.log("Game.qml: created world " + worldObject)
        } else {
            console.log("Game.qml: world not ready")
            component.statusChanged.connect(finishWorld());
        }
    }

    function finishWorld() {
        console.log("Game: finish world")
        if (worldObject.status == Component.Ready) {
            worldObject = component.createObject(game, {"pet": pet, "anchors.fill": game})
            if (worldObject == null) {
                // Error Handling
                console.log("Error creating world");
            }
        } else if (worldObject.status == Component.Error) {
            // Error Handling
            console.log("Error loading world:", worldObject.errorString());
        }
    }
}
