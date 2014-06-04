import QtQuick 2.2
import com.blogspot.iamboke 1.0

/**
 * Pet4
 * 
 * A type of abstract pet.
 */
AbstractPet {
    petType: PetModel.PET4
    content: Image {
        anchors.fill: parent
        source: isDead ? "qrc:/images/rip.png" : "qrc:/images/pet4.png"
    }
}
