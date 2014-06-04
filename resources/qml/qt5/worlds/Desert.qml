import "elements"

/**
 * Desert
 * 
 * An abstract world that looks like a Desert
 */
AbstractWorld {
    color: "#b1c2c2"

    spriteBottom: height - field.height;

    DesertField {
        id:field
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    Cactus {
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 50
        anchors.bottom: field.top
        anchors.bottomMargin: 0
    }

    Cactus {
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 50
        anchors.bottom: field.top
        anchors.bottomMargin: 0
    }

    Cactus {
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: field.top
        anchors.bottomMargin: 0
    }

    Tumbleweed {
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: field.top
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
