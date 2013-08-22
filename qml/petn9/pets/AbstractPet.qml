// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "js/_private.js" as JObjects
import "../js/UIConstants.js" as UI
import "../QmlLogger/qmllogger/Logger.js" as Console

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

  */
Rectangle {
    id: abstractPet
    width: 100
    height: 62
    color: "black"

    property bool doStandardAnimations

    /**
      Sets the collision callback to detect the boundaries of pet movement.
      @param cb is the callback
      */
    function setCollisionCallback(cb) {
        JObjects.register(abstractPet).callback = cb
    }

    function performAnimation() {
        Console.verbose("AbstractPet.qml: performing action " + doStandardAnimations)
        var rand = Math.random()
        var cb = JObjects.register(abstractPet)
        cb = !!cb ? cb.callback : cb
        var cbExists = !!cb

        var delta = UI.PET_MOVEMENT


        if(rand <= .25 && cbExists && cb(x + delta)) {
            //go right
            x += delta
        } else if(rand <= .5 && cbExists && cb(x - delta)) {
            //go left
            x -= delta
        } else if(rand <= .75) {
            //face left
            reflectLeft.angle = 180
            Console.debug("AbstractPet.qml: pet reflected " + reflectLeft.angle + " " + reflectLeft.origin.x + " " + reflectLeft.origin.y)

        } else {
            //face right
            reflectLeft.angle = 0
            Console.debug("AbstractPet.qml: pet reflected " + reflectLeft.angle + " " + reflectLeft.origin.x + " " + reflectLeft.origin.y)

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
        interval: 300
        running: doStandardAnimations
        repeat: true
        onTriggered: {
            performAnimation();
        }
    }
}
