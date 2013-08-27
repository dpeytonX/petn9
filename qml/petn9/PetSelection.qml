// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "pets"

import "js/SpriteFunctions.js" as Sprite
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  FirstRunpetSelection.qml

  Presents the user with pet selections. To be run if there are no pets stored.

  */
DefaultPage {
    id: petSelection

    content: Item {
        anchors.fill: parent

        Text {
            id: title
            text: qsTr("Choose your pet")
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 22
            color: "black"
            anchors.top: parent.top
        }

        Item {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height - 50

            Row {
                anchors.centerIn: parent

                spacing: (parent.width - 100 * 4) / 5

                function petCreated(petItem) {
                    petItem.setCollisionCallback(demoMovement)
                    petItem.doStandardAnimations = true
                }

                function demoMovement(x) {
                    return false
                }

                Pet1 {
                    onPetClicked: {
                        petSelection.pageStack.push(Qt.resolvedUrl("NameSelection.qml"), {"petType": PetModel.PET1})
                    }
                    doStandardAnimations: true
                    Component.onCompleted: setCollisionCallback(parent.demoMovement)
                }

                Pet2 {
                    onPetClicked: {
                        petSelection.pageStack.push(Qt.resolvedUrl("NameSelection.qml"), {"petType": PetModel.PET2})
                    }
                    doStandardAnimations: true
                    Component.onCompleted: setCollisionCallback(parent.demoMovement)
                }

                Pet3 {
                    onPetClicked: {
                        petSelection.pageStack.push(Qt.resolvedUrl("NameSelection.qml"), {"petType": PetModel.PET3})
                    }
                    doStandardAnimations: true
                    Component.onCompleted: setCollisionCallback(parent.demoMovement)
                }

                Pet4 {
                    onPetClicked: {
                        petSelection.pageStack.push(Qt.resolvedUrl("NameSelection.qml"), {"petType": PetModel.PET4})
                    }
                    doStandardAnimations: true
                    Component.onCompleted: setCollisionCallback(parent.demoMovement)
                }
            }
        }
    }
}

