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

    AdminWindow{
        id: adminWindow
        anchors.fill: parent
        visible: false

        function logOut(){
            visible = false
            changeWindowSize(640, 480)
            loginWindow.visible = true
        }
    }

    ManagerWindow{
        id: managerWindow
        anchors.fill: parent
        visible: false

        function logOut(){
            visible = false
            changeWindowSize(640, 480)
            loginWindow.visible = true
        }
    }

    Connections{
        target: BackendRepo

        function onAuthAccepted(username, userType){
            changeWindowSize(1024, 640)
            if(userType === "Admin"){
                adminWindow.visible = true
                adminWindow.userName = username
            }else if(userType === "Manager"){
                managerWindow.visible = true
                managerWindow.userName = username
            }
        }
        function onAuthDenied(){
            console.log("Authentication failed")
        }
    }

    function changeWindowSize(new_width, new_height){
        mainWindow.visible = false
        if(new_width)mainWindow.width = new_width
        if(new_height)mainWindow.height = new_height
        loginWindow.visible = false
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
        mainWindow.visible = true
    }
}
