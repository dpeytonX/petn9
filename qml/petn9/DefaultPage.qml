import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import com.blogspot.iamboke 1.0

/**
  DefaultPage.qml
  
  A page element with common view settings.
  */
Item {
    id: page
    //orientationLock: Manager.isSimulator() ? PageOrientation.Automatic : PageOrientation.LockLandscape
    
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
