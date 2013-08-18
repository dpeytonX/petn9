// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import "pets"

Rectangle {
    width: ScreenWidth
    height: ScreenHeight
    color: "#b7fcff"

    /** Must be defined by sub-elements to provide Sprite boundaries*/
    property real spriteBottom

    Component.onCompleted: {
        console.log(height)
        console.log(width)
    }

    onSpriteBottomChanged: {
        console.log("new sprite bottom: " + spriteBottom)
    }

    Pet1 {
        x: 0
        y: spriteBottom - height
        z: 50
    }
}
