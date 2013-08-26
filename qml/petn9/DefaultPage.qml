// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

/**
  DefaultPage.qml
  
  A page element with common view settings.
  */
Page {
    id: page
    orientationLock: Manager.isSimulator() ? PageOrientation.Automatic : PageOrientation.LockLandscape
    
    property alias content: backgroundRect.children
    Rectangle {
        id: backgroundRect
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#f3abe6"
            }
            
            GradientStop {
                position: 1
                color: "#5e0f64"
            }
        }
        anchors.fill: parent
    }
}
