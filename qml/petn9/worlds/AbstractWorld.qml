// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "../js/SpriteFunctions.js" as Sprite
import "../pets"

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

    property Pet pet

    /** Must be defined by sub-elements to provide Sprite boundaries*/
    property real spriteBottom: ScreenHeight
    property real spriteTop: 0
    property real spriteLeft: 0
    property real spriteRight: ScreenWidth
    property AbstractPet petItem

    onSpriteBottomChanged: {
        console.log("AbstractWorld.qml: new sprite bottom: " + spriteBottom)
        if(!!petItem) {
            petItem.y = spriteBottom - petItem.height
            console.log("AbstractWorld.qml: pet y " + petItem.y)
        }
    }

    onPetItemChanged: {
        console.log("AbstractWorld.qml: pet object obtained")
        if(!!petItem) {
            petItem.setCollisionCallback(isCollisionFree)
            petItem.doStandardAnimations = true
            petItem.x = (ScreenWidth - petItem.width) / 2
            petItem.y = spriteBottom - petItem.height
            console.log("AbstractWorld.qml: pet position ("+ petItem.x +"," + petItem.y+")")
        }
    }

    onPetChanged: {
        Sprite.createPet("../pets/", pet.type, world, {"z": 50}, createPetHandler)
    }

    function createPetHandler(component) {
        console.log("AbstractWorld.qml: Pet callback handler with pet " + component)
        world.petItem = component
    }

    function isCollisionFree(x) {
        console.log("AbstractWorld.qml: pet collision detection at " + x)
        return spriteLeft <= x && x <= spriteRight
    }
}
