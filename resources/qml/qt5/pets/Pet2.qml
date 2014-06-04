import QtQuick 2.2
import com.blogspot.iamboke 1.0

/**
 * Pet2
 * 
 * A type of abstract pet.
 */
AbstractPet {
    petType: PetModel.PET2
    content: Image {
        anchors.fill: parent
        source: isDead ? "qrc:/images/rip.png" : "qrc:/images/pet2.png"
    }
}
