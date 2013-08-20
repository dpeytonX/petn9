// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

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
                console.log("FirstRunWizard.qml: got pet " + currentPet);
                wizard.pageStack.push(Qt.resolvedUrl("Game.qml"), {"pet": Manager.pets[0], "world": Manager.getWorld()})
            }

            MouseArea {
                id:petArea1
                width: 100
                height: 100
                property string qml: "pets/Pet1.qml"

                Component.onCompleted: {
                    var component = Qt.createComponent(qml)
                    if(component.status == Component.Ready) {
                        component.createObject(petArea1)
                    }
                }

                onClicked: {
                    console.log(qml + " was clicked.")
                    parent.launchWorld(Manager.createPet(0));
                }
            }

            MouseArea {
                id:petArea2
                width: 100
                height: 100
                property string qml: "pets/Pet2.qml"

                Component.onCompleted: {
                    var component = Qt.createComponent(qml)
                    if(component.status == Component.Ready) {
                        component.createObject(petArea2)
                    }
                }

                onClicked: {
                    console.log(qml + " was clicked.")
                    parent.launchWorld(Manager.createPet(1));
                }
            }
            MouseArea {
                id:petArea3
                width: 100
                height: 100
                property string qml: "pets/Pet3.qml"

                Component.onCompleted: {
                    var component = Qt.createComponent(qml)
                    if(component.status == Component.Ready) {
                        component.createObject(petArea3)
                    }
                }

                onClicked: {
                    console.log(qml + " was clicked.")
                    parent.launchWorld(Manager.createPet(2))
                }
            }
            MouseArea {
                id:petArea4
                width: 100
                height: 100
                property string qml: "pets/Pet4.qml"

                Component.onCompleted: {
                    var component = Qt.createComponent(qml)
                    if(component.status == Component.Ready) {
                        component.createObject(petArea4)
                    }
                }

                onClicked: {
                    console.log(qml + " was clicked.")
                    parent.launchWorld(Manager.createPet(3));
                }
            }
        }
    }
}

