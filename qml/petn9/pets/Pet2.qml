// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

AbstractPet {
    width: 100
    height: 100
    color: "#00000000"
    opacity: 1

    Image {
        id: image1
        anchors.fill: parent
        source: "qrc:/images/pet2.png"
    }
}
