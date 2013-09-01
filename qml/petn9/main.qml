import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0
import "QmlLogger/qmllogger/Logger.js" as Console

/**
  main.qml

  Contains the page stack and manages common tools
  */
PageStackWindow {
    id: appWindow
    objectName: "appWindow"
    showStatusBar: false

    initialPage: Splash { anchors.fill: parent}

    Component.onCompleted: {
        Console.LOG_PRIORITY = Console.INFO
        pageStack.toolBar.platformStyle = tbStyle
    }

    Component.onDestruction: {
        Console.critical("main.qml: APP IS CLOSING.")
        Manager.saveOnExit()
    }

    ToolBarStyle {
        id: tbStyle
        //inverted: true
    }
}
