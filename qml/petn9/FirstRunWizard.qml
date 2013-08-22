// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

import "js/SpriteFunctions.js" as Sprite
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  FirstRunWizard.qml

  Presents the user with pet selections. To be run if there are no pets stored.

  */
DefaultPage {
    id: wizard
    orientationLock: Manager.isSimulator() ? PageOrientation.Automatic : PageOrientation.LockLandscape

    Text {
        id: title
        text: qsTr("Choose your pet")
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 22
        color: "black"
        anchors.top: parent.top
    }

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: parent.height - 50

        Row {
            anchors.centerIn: parent

            spacing: 10

            function launchWorld(currentPet) {
                Console.info("FirstRunWizard.qml: got pet " + currentPet);
                wizard.pageStack.push(Qt.resolvedUrl("Game.qml"), {"pet": Manager.pets[0], "world": Manager.getWorld()})
            }

            function petCreated(petItem) {
                petItem.setCollisionCallback(demoMovement)
                petItem.doStandardAnimations = true
            }

            function demoMovement(x) {
                return false
            }

            MouseArea {
                id:petArea1
                width: 100
                height: 100

                Component.onCompleted: {
                    Sprite.createPet("pets/", Pet.PET1, petArea1, {}, parent.petCreated)
                }

                onClicked: {
                    Console.debug("FirstRunWizard.qml: " + Pet.PET1 + " was clicked.")
                    parent.launchWorld(Manager.createPet(Pet.PET1));
                }
            }

            MouseArea {
                id:petArea2
                width: 100
                height: 100

                Component.onCompleted: {
                    Sprite.createPet("pets/", Pet.PET2, petArea2, {}, parent.petCreated)
                }

                onClicked: {
                    Console.debug("FirstRunWizard.qml: " + Pet.PET2 + " was clicked.")
                    parent.launchWorld(Manager.createPet(Pet.PET2));
                }
            }
            MouseArea {
                id:petArea3
                width: 100
                height: 100

                Component.onCompleted: {
                    Sprite.createPet("pets/", Pet.PET3, petArea3, {}, parent.petCreated)
                }

                onClicked: {
                    Console.debug("FirstRunWizard.qml: " + Pet.PET3 + " was clicked.")
                    parent.launchWorld(Manager.createPet(Pet.PET3))
                }
            }
            MouseArea {
                id:petArea4
                width: 100
                height: 100

                Component.onCompleted: {
                    Sprite.createPet("pets/", Pet.PET4, petArea4, {}, parent.petCreated)
                }

                onClicked: {
                    Console.debug("FirstRunWizard.qml: " + Pet.PET4 + " was clicked.")
                    parent.launchWorld(Manager.createPet(Pet.PET4));
                }
            }
        }
    }
}

