// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.blogspot.iamboke 1.0

AbstractPet {
    petType: PetModel.PET1
    content: Image {
        anchors.fill: parent
        source: isDead ? "qrc:/images/rip.png" : "qrc:/images/pet1.png"
    }
}
