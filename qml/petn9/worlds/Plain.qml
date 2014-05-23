import "elements"

AbstractWorld {
    color: "#b1c2c2"

    spriteBottom: height - field.height;

    GrassyField {
        id:field
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    Sun {
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Cloud {
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }


}
