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
    tools: gameTools

    signal clean
    signal feed

    Component.onCompleted: {
        var world = Manager.getWorld()
        Sprite.createWorld("worlds/"+world+".qml", game, {"anchors.fill": game}, finishedWorld)
    }

    function finishedWorld(worldObject) {
        worldObject.exitWorld.connect(startOver)
        worldObject.exitGame.connect(gameOver)
        worldObject.removeFromGame.connect(deleteModel)
        clean.connect(worldObject.clearSprites)
        feed.connect(worldObject.feedPet)
    }

    function startOver() {
        Manager.saveOnExit()
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

    ToolBarLayout {
        id: gameTools
        ToolButtonRow {
            ToolIcon {
                iconId: "toolbar-delete"
                onClicked: {
                    deleteModel(-1)
                }
                Component.onCompleted: {
                    Console.trace("Game.qml: tool icon size: " + width + " " + height)
                }
            }

            ToolIcon {
                iconSource: "qrc:/images/icon-feed.png"
                onClicked: {
                    Console.info("Game.qml: Feeding")
                    feed()
                }
            }
        }

        ToolIcon {
            iconId: "toolbar-view-menu"
            onClicked: (mainMenu.status === DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
        }
    }

    Menu {
        id: mainMenu
        visualParent: pageStack
        MenuLayout {

            MenuItem {
                text: qsTr("Quit")
                onClicked: Qt.quit()
            }
        }
    }
}
