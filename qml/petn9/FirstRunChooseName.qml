// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

import "QmlLogger/qmllogger/Logger.js" as Console
import "js/SpriteFunctions.js" as Sprite

DefaultPage {
    id: firstRunName

    property int petType

    function launchWorld() {
        firstRunName.pageStack.push(Qt.resolvedUrl("Game.qml"))
    }

    function petCreated(petItem) {
        petItem.setCollisionCallback(demoMovement)
        petItem.doStandardAnimations = true
    }

    function demoMovement(x) {
        return false
    }

    Text {
        id: title
        text: qsTr("Pick your pet's name")
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 22
        color: "black"
        anchors.top: parent.top
    }

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: parent.height - 50

        Column {
            anchors.fill: parent
            spacing: 20

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                id:petArea1
                width: 100
                height: 100

                Component.onCompleted: {
                    Sprite.createPet("pets/", petType, petArea1, {}, firstRunName.petCreated)
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Type here:")
                }

                TextField {
                    text: ""
                    id: nameInput
                    width: firstRunName.width / 2
                    maximumLength: 10
                    anchors.verticalCenter: parent.verticalCenter
                    validator: RegExpValidator {
                        regExp: /^[A-Za-z]+$/
                    }
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: okButton
                    text: qsTr("OK!")
                    onClicked: {
                        if(Manager.createPet(petType, nameInput.text)) {
                            launchWorld()
                        } else {
                            Console.error("FirstRunChooseName.qml: could not create a pet model")
                        }
                    }
                    enabled: nameInput.acceptableInput
                }
                Button {
                    id: resetButton
                    text: qsTr("Reset")
                    onClicked: {
                        nameInput.text = ""
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        nameInput.text = qsTr("Name")
        nameInput.text = ""
    }
}
