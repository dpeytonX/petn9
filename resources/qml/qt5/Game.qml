import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import com.blogspot.iamboke 1.0

import "/js/SpriteFunctions.js" as SpriteFunctions
import "/js/UIConstants.js" as UI
import "/QmlLogger/Logger.js" as Console

/**
  Game.qml

  Represents the window which contains the environment that the user interacts with.
  */
DefaultPage {
    id: game
    tools: gameTools
    
    signal clean
    signal feed

    Component.onCompleted: {
        var world = Manager.getWorld()
        SpriteFunctions.createWorld(UI.QML_QT5_WORLDS + world + ".qml", game, {"anchors.fill": game}, finishedWorld)
    }

    function finishedWorld(worldObject) {
        Console.debug("Inside finished world");
        worldObject.exitWorld.connect(startOver)
        worldObject.exitGame.connect(gameOver)
        worldObject.removeFromGame.connect(deleteModel)
        clean.connect(worldObject.clearSprites)
        feed.connect(worldObject.feedPet)
        Manager.updateLastAppStart()
    }

    function startOver() {
        Manager.reset()
        game.pageStack.replace(Qt.resolvedUrl("Splash.qml"))
    }

    function deleteModel(spriteId) {
        Console.debug("Game.qml: deleting sprite " + spriteId)
        //Create a blank sprite model
        var s = Manager.getNewSpriteModel()
        //Make sure that we target ALL models
        s.typeId = spriteId == -1 ? SpriteModel.ALL : SpriteModel.OTHER
        s.id = spriteId
        Manager.deleteSpriteModel(s)
        Console.info("Game.qml: Cleaning")
        clean()
    }

    function gameOver() {
        Qt.quit();
    }

    ToolBar {
      id: gameTools
    RowLayout {
        
        Row {
            ToolButton {
                iconSource: "qrc:/icons/icon-delete.png"
                onClicked: {
                    deleteModel(-1)
                }
                Component.onCompleted: {
                    Console.trace("Game.qml: tool icon size: " + width + " " + height)
                }
            }

            ToolButton {
                iconSource: "qrc:/icons/icon-feed.png"
                onClicked: {
                    Console.info("Game.qml: Feeding")
                    feed()
                }
            }
        }
    }}

}
