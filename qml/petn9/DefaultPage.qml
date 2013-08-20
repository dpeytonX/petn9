// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import com.blogspot.iamboke 1.0

/**
  DefaultPage.qml

  A page element with common view settings.
  */
Page {
    id: wizard
    orientationLock: Manager.isSimulator() ? PageOrientation.Automatic : PageOrientation.LockLandscape

}
