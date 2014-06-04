import QtQuick 2.2
import com.blogspot.iamboke 1.0

/**
 * Pet1
 * 
 * A type of abstract pet.
 */
AbstractPet {
    petType: PetModel.PET1
    content: Image {
        anchors.fill: parent
        source: isDead ? "qrc:/images/rip.png" : "qrc:/images/pet1.png"
    }
}
