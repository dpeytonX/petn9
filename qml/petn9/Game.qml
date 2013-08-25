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

    Component.onCompleted: {
        var world = Manager.getWorld()
        Sprite.createWorld("worlds/"+world+".qml", game, {"anchors.fill": game}, finishedWorld)
    }

    function finishedWorld(worldObject) {
        worldObject.exitWorld.connect(startOver)
        worldObject.exitGame.connect(gameOver)
    }

    function startOver() {
        Manager.saveOnExit()
        game.pageStack.replace(Qt.resolvedUrl("Splash.qml"))
    }

    function gameOver() {
        Qt.quit();
    }
}
