// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "../pets"

import "../QmlLogger/qmllogger/Logger.js" as Console
import "../js/_private.js" as JObjects
import "../js/SpriteFunctions.js" as Sprite
import "../js/UIConstants.js" as UI

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
    signal removeFromGame (int spriteId)

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
            petItem.setFoodCallback(hasFood)
            petItem.doStandardAnimations = true
        }
        petItem.x = (ScreenWidth - petItem.width) / 2
        petItem.y = spriteBottom - petItem.height
        petItem.petClicked.connect(petClicked)
        Console.debug("AbstractWorld.qml: pet position ("+ petItem.x +"," + petItem.y+")")
        Console.debug("AbstractWorld.qml: pet is " + (pet.dead ? "dead" : "alive"))

        var foodObjectArray = JObjects.register(world).foodObjectArray
        if(!!foodObjectArray && !!foodObjectArray.length) {
            petItem.doFeedingAnimation = true
        }
    }

    onPetChanged: {
        Sprite.createPet("../pets/", pet.type, world, {"z": 100}, createPetHandler)
    }

    function clearSprites() {
        //reset sprite map
        Console.log("AbstractWorld.qml: clearing sprites")
        var newSpriteModels = Manager.sprites;
        var spriteObjectArray = JObjects.register(world).spriteObjectArray;

        for(var i = 0; i < spriteObjectArray.length; i++) {
            var s = spriteObjectArray[i]
            Console.log("AbstractWorld.qml: Checking model " + s.spriteId)
            var found = false
            for(var j = 0; j < newSpriteModels.length; j++) {
                var t = newSpriteModels[j]
                if(s.spriteId == t.id) {
                    found = true
                    break;
                }
            }
            if(!found) {
                Console.log("deleting item " + s)
                s.destroy() //Remove Item from view
                spriteObjectArray.splice(i,1) //Remove item from store

                var foodObjectArray = JObjects.register(world).foodObjectArray

                for(var k = 0; k < foodObjectArray.length; k++) {
                    var u = foodObjectArray[k]
                    if(s.spriteId = u.spriteId) {
                        foodObjectArray.splice(k,1)
                        break;
                    }
                }

                i -= 1 //Reset accumulator
            }
        }
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

    function hasFood(x) {
        var collision = isCollisionFree(x)

        var foodObjectArray = JObjects.register(world).foodObjectArray;
        var foodExists = !!foodObjectArray.length
        Console.log("AbstractWorld.qml: foodExists " + foodExists)
        var firstFood = foodObjectArray[0]
        var dir = null
        if(!!firstFood) {
            dir = firstFood.x - petItem.x < 0 ? petItem.moveLeft : petItem.moveRight
            dir = Math.abs(firstFood.x - petItem.x) <= petItem.width ? null : dir
        }

        if(dir === null && !!firstFood) {
            Console.log("AbstractWorld.qml: removing from game " + firstFood.spriteId)
            removeFromGame(firstFood.spriteId)
        }

        return {
            canMove: collision,
            gotFood: foodExists,
            direction: dir
        }
    }

    function spawnSprites() {
        Console.verbose("AbstractWorld.qml: drawing left oversprites ")
        var spriteModels = Manager.sprites
        Console.debug("AbstractWorld.qml: retrieved sprite models " + spriteModels)
        if(!spriteModels) return
        Console.debug("AbstractWorld.qml: spriteModels.length " + spriteModels.length)
        for(var i = 0; i < spriteModels.length; i++) {
            var currentModel = spriteModels[i]
            Console.log("AbstractWorld.qml: sprite Id " + currentModel.id)
            Sprite.createSprite("../objects/", currentModel.typeId, world, {"x": currentModel.x, "y": currentModel.y, "z": 5, "spriteId": currentModel.id}, spriteCreated)
        }
    }

    function spawnPoop() {
        Console.debug("AbstractWolrd.qml: spawning poop action ")

        var rand = Math.random()
        var spriteModels = Manager.sprites
        if (rand <= UI.PET_POOP_CHANCE) {
            if(spriteModels.length >= UI.MAX_POOP_OBJECTS) {
                Console.info("AbstractPet.qml: Max poop objects reached")
                return
            }

            Console.debug("AbstractPet.qml: pet just pooped " + UI.PET_POOP_CHANCE)
            Sprite.createSprite("../objects/", SpriteModel.POOP, world.parent, {"z": 5}, poopCreated)
        }
    }

    function feedPet() {
        Console.debug("AbstractWolrd.qml: feeding pet action ")
        Sprite.createSprite("../objects/", SpriteModel.FOOD, world.parent, {"z": 5}, foodCreated)
    }

    function spriteCreated(spriteItem) {
        var spriteObjectArray = JObjects.register(world).spriteObjectArray
        spriteObjectArray[spriteObjectArray.length] = spriteItem
        Console.log("AbstractWorld: sprite object array " + spriteObjectArray)

        if(spriteItem.type == SpriteModel.FOOD) {
            var foodObjectArray = JObjects.register(world).foodObjectArray
            foodObjectArray[foodObjectArray.length] = spriteItem
            Console.log("AbstractWorld.qml: food object array " + foodObjectArray)
            if(!!petItem) {
                petItem.doFeedingAnimation = true
            }
        }
    }

    function poopCreated(spriteItem) {
        spriteItem.x = petItem.x
        spriteItem.y = petItem.y + spriteItem.height
        var spriteModel = Manager.createSprite(spriteItem.type, spriteItem.x, spriteItem.y)
        Console.log("AbstractWorld.qml: poop created " + spriteModel.id)
        spriteItem.spriteId = spriteModel.id
        spriteCreated(spriteItem)
    }

    function foodCreated(spriteItem) {
        Console.log("Abstract.qml: food item " + spriteItem)
        spriteItem.x = world.width - petItem.x - petItem.width
        spriteItem.y = petItem.y + spriteItem.height
        var spriteModel = Manager.createSprite(spriteItem.type, spriteItem.x, spriteItem.y)
        Console.log("AbstractWorld.qml: food created " + spriteModel.id)
        spriteItem.spriteId = spriteModel.id
        spriteCreated(spriteItem)
    }

    function initSpriteObjectArray() {
        var spriteObjectArray = JObjects.register(world).spriteObjectArray
        if(!spriteObjectArray) {
            JObjects.register(world).spriteObjectArray = []
            JObjects.register(world).foodObjectArray = []
        }
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
        initSpriteObjectArray()
        spawnSprites();
    }

    Timer {
        id: poopTimer
        interval: UI.PET_POOP_TIMER
        running: true
        repeat: true
        onTriggered: {
            spawnPoop()
        }
    }
}
