import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtMultimedia 5.0
import "/QmlLogger/Logger.js" as Console
import "/js/SpriteFunctions.js" as SpriteFunctions
import "/js/UIConstants.js" as UI

/**
  main.qml

  Contains the page stack and manages common tools
  */
ApplicationWindow {
    id: appWindow
    objectName: "appWindow"
    visible: true
    width: Math.min(Screen.desktopAvailableWidth, 800)
    height: Math.min(Screen.desktopAvailableHeight, 600)
    x: (Screen.desktopAvailableWidth - width ) / 2
    y: (Screen.desktopAvailableHeight - height) / 2

    
    property alias pageStack: stackView
    
    StackView {
      id: stackView
      anchors.fill: parent
      
      initialItem: Splash { id: splash }
    }
    
    SoundEffect {
      id: petClickSound
      volume: 1
      source: SpriteFunctions.locateSoundFile(UI.SND_PET_CLICK)//Qt.resolvedUrl(SpriteFunctions.locateSoundFile(UI.SND_PET_CLICK))
    }

    Component.onCompleted: {
        Console.LOG_PRIORITY = Console.DEBUG
        if(Console.LOG_PRIORITY == Console.DEBUG) {
	    Console.debug(petClickSound.source)
	}
    }

    Component.onDestruction: {
        Console.critical("main.qml: APP IS CLOSING.")
    }
}
