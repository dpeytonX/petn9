// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.blogspot.iamboke 1.0
import ".."

import "../js/UIConstants.js" as UI

Sprite {
    property int type
    width: UI.GAME_OBJECT_WIDTH
    height: UI.GAME_OBJECT_HEIGHT
    z: 10
}
