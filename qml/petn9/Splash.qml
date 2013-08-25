import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

import "QmlLogger/qmllogger/Logger.js" as Console

/**
  Splash.qml

  Presents the game logo and start options to the user.
  */
DefaultPage {

    property string world
    property variant worldObject

    Rectangle {
        id: splash
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#f3abe6"
            }

            GradientStop {
                position: 1
                color: "#5e0f64"
            }
        }
        anchors.fill: parent


        Text {
            anchors.horizontalCenter: splash.horizontalCenter
            anchors.verticalCenter: splash.verticalCenter
            color: "#ffffff"
            text: qsTr("PetN9")
            font.pointSize: 31
        }

        Column {
            spacing: 10
            anchors.horizontalCenter: splash.horizontalCenter
            anchors.bottom: splash.bottom
            anchors.bottomMargin: 20

            Button {
                onClicked: {
                    if(!Manager.pets.length) {
                        Console.info("Splash.qml: empty pets. Creating first run wizard.")
                        appWindow.pageStack.push(Qt.resolvedUrl("FirstRunWizard.qml"))
                    } else {
                        Console.info("Splash.qml: has pets, creating game")
                        appWindow.pageStack.push(Qt.resolvedUrl("Game.qml"))
                    }
                }

                Component.onCompleted: {
                    text = !!Manager.pets.length ? qsTr("Resume") : qsTr("Start")
                }
            }
        }
    }
}
