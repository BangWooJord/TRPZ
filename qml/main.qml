import QtQuick 2.15
import QtQuick.Window 2.2

Window{
    id: mainWindow
    width: 640
    height: 480
    visible: true

    color: '#add8e6'

    LoginWindow{
        id: loginWindow
        anchors.fill: parent
    }

    Connections{
        target: BackendRepo

        function onAuthAccepted(){
            mainWindow.visible = false
            mainWindow.width = 1024
            loginWindow.visible = false
            x = Screen.width / 2 - width / 2
            y = Screen.height / 2 - height / 2
            mainWindow.visible = true
        }
        function onAuthDenied(){
            console.log("Authentication failed")
        }
    }
}
