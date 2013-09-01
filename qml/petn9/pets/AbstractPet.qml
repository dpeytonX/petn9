// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.blogspot.iamboke 1.0
import ".."

import "../QmlLogger/qmllogger/Logger.js" as Console
import "../js/_private.js" as JObjects
import "../js/SpriteFunctions.js" as Sprite
import "../js/UIConstants.js" as UI

/**
  AbstractPet.qml

  Common settings to Pet objects

  Properties:
  doStandardAnimations (bool) - set to true to perform the standard animation after each animation loop. Set to false to switch off.


  Elements
  animationTimer (Timer) - performs the animation loop.
        Subclasses may choose to alter the function of the timer.
        By default, it runs if doStandardAnimations is true.

  Functions
  setCollisionCallback(cb) - is the collision detection Javascript callback.
  Additionally, cb is a parameter in the following form:
  function cb(x) { return bool }
  Where x is a real number determining the next x position the Pet will move,
  and returns true if the move is legal and false, otherwise.

  setFoodCallback(cb) - is the food detection Javascript callback.
  Additionally, cb is a parameter in the following form:
  function cb(x) { return
    {
      canMove: bool,
      gotFood: bool,
      direction: AbstractPet.moveLeft | AbstractPet.moveRight
    }
  }
  Where x is a real number determining the next x position the Pet will move,
  and returns true if the move is legal and false, otherwise.
  */
Sprite {
    id: abstractPet
    width: UI.PET_WIDTH
    height: UI.PET_WIDTH
    z: 50

    property int petType
    property bool doStandardAnimations
    property bool doFeedingAnimation
    property alias content: mouseArea.children
    property int moveLeft: 0
    property int moveRight: 1

    signal petClicked

    MouseArea {
        anchors.fill: parent
        id: mouseArea

        Component.onCompleted: {
            mouseArea.clicked.connect(petClicked)
        }
    }

    /**
      Sets the collision callback to detect the boundaries of pet movement.
      @param cb is the callback
      */
    function setCollisionCallback(cb) {
        JObjects.register(abstractPet).callback = cb
    }

    /**
      Sets the collision callback to detect food boundary.
      @param cb is the callback
      */
    function setFoodCallback(cb) {
        JObjects.register(abstractPet).foodCallback = cb
    }

    function performFeedingAnimation() {
        doStandardAnimations = false
    }

    function performAnimation() {
        Console.verbose("AbstractPet.qml: performing action " + doStandardAnimations)
        var rand = Math.random()
        var cb = JObjects.register(abstractPet)
        cb = !!cb ? cb.callback : cb
        var cbExists = !!cb

        var delta = UI.PET_MOVEMENT


        if(rand <= .4 && cbExists && cb(x + width + delta)) {
            //go right
            x += delta
        } else if(rand <= .8 && cbExists && cb(x - delta)) {
            //go left
            x -= delta
        } else if(rand <= .9) {
            //face left
            reflectLeft.angle = 180
            Console.verbose("AbstractPet.qml: pet reflected " + reflectLeft.angle + " " + reflectLeft.origin.x + " " + reflectLeft.origin.y)

        } else {
            //face right
            reflectLeft.angle = 0
            Console.verbose("AbstractPet.qml: pet reflected " + reflectLeft.angle + " " + reflectLeft.origin.x + " " + reflectLeft.origin.y)

        }
    }

    function spriteCreated(spriteObject) {
        if(!!spriteObject) {
            Console.debug("AbstractPet.qml: sprite object created")
            spriteObject.x = abstractPet.x
            spriteObject.y = abstractPet.y + spriteObject.height
            Manager.createSprite(spriteObject.type, spriteObject.x, spriteObject.y)
        } else {
            Console.error("AbstractPet.qml: Error loading sprite object")
        }
    }

    transform: Rotation {
        id: reflectLeft
        axis {x: 0; y: 1; z: 0}
        origin.x: width / 2
        origin.y: height / 2
        angle: 0
    }

    Rotation {
        id: reflectRight

        axis {x: 0; y: 1; z: 0}
        angle: -180
    }

    Timer {
        id: animationTimer
        interval: UI.PET_ANIMATION_TIMER
        running: doStandardAnimations
        repeat: true
        onTriggered: {
            performAnimation()
        }
    }

    Timer {
        id: foodTimer
        interval: UI.PET_ANIMATION_TIMER
        running: doFeedingAnimation
        repeat: true
        onTriggered: {
            performFeedingAnimation()
        }
    }
}
