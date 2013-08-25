// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "../js/SpriteFunctions.js" as Sprite
import "../pets"
import "../QmlLogger/qmllogger/Logger.js" as Console

/**
  AbstractWorld.qml

  This is the element that paints the scenery and Pet element on screen. Has common objects which specific worlds use.

  Properties
  spriteBottom (real) - bottom boundary for the pet (suggested to override)
  spriteTop (real) - bottom boundary for the pet
  spriteLeft (real) - left boundary for the pet
  spriteRight (real) - right boundary for the pet
  pet (Pet) - the QtObject backed model
  petItem (AbstractPet) - the visual pet representation
  */

Rectangle {
    id:world

    property PetModel pet

    /** Must be defined by sub-elements to provide Sprite boundaries*/
    property real spriteBottom: ScreenHeight
    property real spriteTop: 0
    property real spriteLeft: 0
    property real spriteRight: ScreenWidth
    property AbstractPet petItem

    signal exitWorld
    signal exitGame

    onSpriteBottomChanged: {
        Console.debug("AbstractWorld.qml: new sprite bottom: " + spriteBottom)
        if(!!petItem) {
            petItem.y = spriteBottom - petItem.height
            Console.debug("AbstractWorld.qml: pet y " + petItem.y)
        }
    }

    onPetItemChanged: {
        Console.info("AbstractWorld.qml: pet object obtained")
        if(!!petItem && !pet.dead) {
            petItem.setCollisionCallback(isCollisionFree)
            petItem.doStandardAnimations = true
            petItem.doSpawnObjects = true
        }
        petItem.x = (ScreenWidth - petItem.width) / 2
        petItem.y = spriteBottom - petItem.height
        petItem.petClicked.connect(petClicked)
        Console.debug("AbstractWorld.qml: pet position ("+ petItem.x +"," + petItem.y+")")
        Console.debug("AbstractWorld.qml: pet is " + (pet.dead ? "dead" : "alive"))
    }

    onPetChanged: {
        Sprite.createPet("../pets/", pet.type, world, {}, createPetHandler)
    }

    function petClicked() {
        Console.debug("AbstractWorld.qml: Pet clicked")
        if(pet.dead) {
            restartGame.open()
        }
    }

    function createPetHandler(component) {
        Console.info("AbstractWorld.qml: Pet callback handler with pet " + component)
        world.petItem = component
    }

    function isCollisionFree(x) {
        Console.trace("AbstractWorld.qml: pet collision detection at " + x)
        return spriteLeft <= x && x <= spriteRight
    }

    function spawnSprites() {
        Console.verbose("AbstractWorld.qml: drawing left oversprites ")
        var spriteModels = []; spriteModels = Manager.sprites
        Console.debug("AbstractWorld.qml: retrieved sprite models " + spriteModels)
        if(!spriteModels) return
        Console.debug("AbstractWorld.qml: spriteModels.length " + spriteModels.length)
        for(var i = 0; i < spriteModels.length; i++) {
            var currentModel = spriteModels[i]
            var component
            switch(currentModel.typeId) {
            case SpriteModel.POOP:
                component = Qt.createComponent("../objects/Poop.qml")
                break
            default:
                component = Qt.createComponent("../objects/Poop.qml")
                break
            }
            if(component.status == Component.Ready) {
                var spriteItem = component.createObject(world)
                spriteItem.x = currentModel.x
                spriteItem.y = currentModel.y
                Console.debug("AbstractWorld.qml: created sprite at (" + x + "," + y + ")")
            } else if (component.status == Component.Error) {
                // Error Handling
                Console.error("AbstractWorld.qml: Error loading sprite:", component.errorString());
            }
        }
        spriteModels = []
    }


    QueryDialog {
        id: restartGame
        titleText: qsTr("Game Over")
        message: qsTr("You're pet is dead.")
        acceptButtonText: qsTr("Back to Title")
        rejectButtonText: qsTr("Quit")

        onAccepted: {
            Console.info("AbstractWorld.qml: do over")
            exitWorld()
        }
        onRejected: {
            Console.debug("AbstractWorld.qml: quit left")
            exitGame()
        }
    }


    Component.onCompleted: {
        pet = Manager.currentPet
        spawnSprites();
    }
}
