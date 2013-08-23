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

            MouseArea {
                id:petArea1
                width: 100
                height: 100
                property int type: PetModel.PET1

                Component.onCompleted: {
                    Sprite.createPet("pets/", type, petArea1, {}, parent.petCreated)
                }

                onClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": type})
                }

                onPressed: {
                    highlight.anchors.centerIn = petArea1
                    highlight.opacity = 1
                }

                Rectangle {
                    id: highlight
                    border.width: 1
                    border.color: "blue"
                    width: 100
                    height: 100
                    opacity: 0
                }

            }


            MouseArea {
                id:petArea2
                width: 100
                height: 100.
                property int type: PetModel.PET2

                Component.onCompleted: {
                    Sprite.createPet("pets/", type, petArea2, {}, parent.petCreated)
                }

                onClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": type})
                }

                onPressed: {
                    highlight2.anchors.centerIn = petArea2
                    highlight2.opacity = 1
                }

                Rectangle {
                    id: highlight2
                    border.width: 1
                    border.color: "blue"
                    width: 100
                    height: 100
                    opacity: 0
                }
            }
            MouseArea {
                id:petArea3
                width: 100
                height: 100
                property int type: PetModel.PET3

                Component.onCompleted: {
                    Sprite.createPet("pets/", type, petArea3, {}, parent.petCreated)
                }

                onClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": type})
                }

                onPressed: {
                    highlight3.anchors.centerIn = petArea3
                    highlight3.opacity = 1
                }

                Rectangle {
                    id: highlight3
                    border.width: 1
                    border.color: "blue"
                    width: 100
                    height: 100
                    opacity: 0
                }
            }
            MouseArea {
                id:petArea4
                width: 100
                height: 100
                property int type: PetModel.PET4

                Component.onCompleted: {
                    Sprite.createPet("pets/", type, petArea4, {}, parent.petCreated)
                }

                onClicked: {
                    wizard.pageStack.push(Qt.resolvedUrl("FirstRunChooseName.qml"), {"petType": type})
                }

                onPressed: {
                    highlight4.anchors.centerIn = petArea4
                    highlight4.opacity = 1
                }

                Rectangle {
                    id: highlight4
                    border.width: 1
                    border.color: "blue"
                    width: 100
                    height: 100
                    opacity: 0
                }
            }
        }
    }
}

