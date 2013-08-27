// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.blogspot.iamboke 1.0

AbstractPet {
    petType: PetModel.DEAD
    content: Image {
        id: image1
        anchors.fill: parent
        source: "qrc:/images/rip.png"
    }
}
