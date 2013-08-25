// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "pets"

import "js/SpriteFunctions.js" as Sprite
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  FirstRunWizard.qml

  Presents the user with pet selections. To be run if there are no pets stored.

  */
DefaultPage {
    id: wizard

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
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": PetModel.PET1})
                }
            }

            Pet2 {
                onPetClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": PetModel.PET2})
                }
            }

            Pet3 {
                onPetClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": PetModel.PET3})
                }
            }

            Pet4 {
                onPetClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": PetModel.PET4})
                }
            }
        }
    }
}

