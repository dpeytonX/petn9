import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

import "js/SpriteFunctions.js" as Sprite
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  Game.qml

  Represents the window which contains the environment that the user interacts with.
  */
DefaultPage {
    id: game

//    property variant worldObject

    Component.onCompleted: {
        var world = Manager.getWorld()
        Sprite.createWorld("worlds/"+world+".qml", game, {"anchors.fill": game}, null)
    }

//    function finishWorld(completedWorld) {
//        Console.debug("Game: finish world")
//        if(!!completedWorld) {
//            worldObject = completedWorld
//        } else {
//            Console.error("Error loading world");
//        }
//    }
}
