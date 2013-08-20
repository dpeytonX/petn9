// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import "../pets"
import com.blogspot.iamboke 1.0

/**
  AbstractWorld.qml

  This is the element that paints the scenery and Pet element on screen. Has common objects which specific worlds use.
  */

Rectangle {
    id:world

    property Pet pet

    /** Must be defined by sub-elements to provide Sprite boundaries*/
    property real spriteBottom

    Component.onCompleted: {
        console.log(height)
        console.log(width)
    }

    onSpriteBottomChanged: {
        console.log("new sprite bottom: " + spriteBottom)
    }

    Item {
        id: petItem
        x: 0
        y: spriteBottom - height
        z: 50
        property AbstractPet myPet
    }

    function createPet(qml) {
        var component = Qt.createComponent(qml);
        if(component.status == Component.Ready) {
            //var petComponent = component.createObject(petItem,{"x": 0, "y": spriteBottom - height, "z": 50})
            var petComponent = component.createObject(petItem,{
                                                          "anchors.bottom": petItem.bottom,
                                                          "anchors.bottomMargin": 0,
                                                          "anchors.left": petItem.left,
                                                          "anchors.leftMargin": 0})
            petItem.myPet = petComponent
            console.log("created pet component at (" + petComponent.x + ", " + petComponent.y + ")")
        }
    }

    onPetChanged: {
        var qml;
        switch(pet.type) {
        case Pet.PET1:
            qml = "../pets/Pet1.qml";
            break;
        case Pet.PET2:
            qml = "../pets/Pet2.qml";
            break;
        case Pet.PET3:
            qml = "../pets/Pet3.qml";
            break;
        case Pet.PET4:
            qml = "../pets/Pet4.qml";
            break;
        default:
            qml = "../pets/Pet1.qml";
            break;
        }
        console.log("pet changed")
        createPet(qml)
    }
}
