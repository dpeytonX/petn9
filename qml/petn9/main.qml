import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  main.qml

  Contains the page stack and manages common tools
  */
ApplicationWindow {
    id: appWindow
    objectName: "appWindow"
    visible: true
    width: ScreenWidth
    height: ScreenHeighta
    flags: W
    //showStatusBar: false

    //initialPage:
    Splash { anchors.fill: parent}

    Component.onCompleted: {
        Console.LOG_PRIORITY = Console.INFO
        //pageStack.toolBar.platformStyle = tbStyle
    }

    Component.onDestruction: {
        Console.critical("main.qml: APP IS CLOSING.")
    }

    /*ToolBarStyle {
        id: tbStyle
        //inverted: true
    }*/
}
