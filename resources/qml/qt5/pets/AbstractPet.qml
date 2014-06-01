import QtQuick 2.2
import QtMultimedia 5.0
import com.blogspot.iamboke 1.0
import "../../../common/widgets"
import "/QmlLogger/Logger.js" as Console
import "/js/_private.js" as JObjects
import "/js/UIConstants.js" as UI
import "/js/SpriteFunctions.js" as SpriteFunctions

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
    property bool doStatusAnimation
    property alias content: mouseArea.children
    property int moveLeft: 0
    property int moveRight: 1
    property bool isDead: false
    property bool isHungry: false
    property bool isSad: false

    signal petClicked

    onIsDeadChanged: {
        if(isDead)
            reflectLeft.angle = 0
    }

    onPetClicked: {
        Console.info("AbstractPet.qml: pet clicked")
	Console.info("AbstractPet.qml: playing sound")
	
	petClickSound.play()
	
        if(isHungry) {
            statusIcon.source = "qrc:/images/hungry.png"
        } else if(!isSad) {
            statusIcon.source ="qrc:/images/happy.png"
        }
        statusIcon.visible = !isDead && doStatusAnimation
    }

    MouseArea {
        anchors.fill: parent
        id: mouseArea

        Component.onCompleted: {
            mouseArea.clicked.connect(petClicked)
        }
    }

    Image {
        id: statusIcon
        width: 25
        height: 25
        visible: false
        z: 100
        anchors.bottom: parent.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
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
        doFeedingAnimation = false
        doStandardAnimations = false
        var cb = JObjects.register(abstractPet).foodCallback
        if(!cb) {
            doStandardAnimations = true
            return
        }
        var result = cb(x)
        var delta = UI.PET_MOVEMENT

        if(!result.gotFood) {
            doStandardAnimations = true
            return
        }

        if(result.direction != null) {
            delta *= (result.direction == moveLeft ? -1 : 1)
        }

        result = cb(x + width + delta)
        if(!result.gotFood) {
            doStandardAnimations = true
            return
        }

        if(result.canMove) {
            x += delta
        }
        doFeedingAnimation = true
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
        running: !isDead && doStandardAnimations
        repeat: true
        onTriggered: {
            performAnimation()
        }
    }

    Timer {
        id: foodTimer
        interval: UI.PET_ANIMATION_TIMER
        running: !isDead && doFeedingAnimation
        repeat: true
        onTriggered: {
            performFeedingAnimation()
        }
    }

    Timer {
        id: statusIconTimer
        triggeredOnStart: false
        interval: UI.STAT_ANIMATION_TIMER
        running: statusIcon.visible
        repeat: false
        onTriggered: {
            statusIcon.visible = false
        }
    }
}
