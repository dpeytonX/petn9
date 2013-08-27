// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

import "QmlLogger/qmllogger/Logger.js" as Console
import "js/SpriteFunctions.js" as Sprite
import "js/UIConstants.js" as UI

/**
  NameSelection.qml

  Allows user to set the Pet's name.

  */
DefaultPage {
    id: nameSelection
    tools: nameSelectionTools
    property int petType

    content: Item {
        anchors.fill: parent
        id: firstRunName

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

        Item {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height - 50

            Column {
                anchors.fill: parent
                anchors.topMargin: 20
                spacing: 20

                Sprite {
                    anchors.horizontalCenter: parent.horizontalCenter
                    id:petArea1
                    width: UI.PET_WIDTH
                    height: UI.PET_HEIGHT

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

                ButtonRow {
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: okButton
                        text: qsTr("OK!")
                        onClicked: {
                            if(Manager.createPet(petType, nameInput.text)) {
                                nameSelection.pageStack.push(Qt.resolvedUrl("Game.qml"))
                            } else {
                                Console.error("NameSelection.qml: could not create a pet model")
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
    }

    ToolBarLayout {
        id: nameSelectionTools
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: pageStack.pop();
        }
    }

    Component.onCompleted: {
        nameInput.text = qsTr("Name")
        nameInput.text = ""
    }
}
