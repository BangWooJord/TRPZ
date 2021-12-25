import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    Button{
        id: logoutBtn
        text: "Вийти"
        width: 100
        height: 50
        anchors{
            left: parent.left
            leftMargin: 15
            bottom: parent.bottom
            bottomMargin: 15
        }
        background: Rectangle{
            radius: 15
            border.width: 0
        }
        font.pixelSize: 16
        onClicked: {
            logoutPopup.open()
        }
    }
    Popup{
        id: logoutPopup
        width: 320
        height: 160
        dim: true
        background: Rectangle{
            radius: 15
            border.width: 0
        }
        anchors.centerIn: parent

        Label{
            id: logoutLbl
            width: 300
            anchors{
                top: parent.top
                topMargin: 15
                horizontalCenter: parent.horizontalCenter
            }
            text: "Ви впевнені що хочете вийти з акаунту?"
            wrapMode: Text.Wrap
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Row{
            anchors{
                top: logoutLbl.bottom
                topMargin: 15
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 10
            Button{
                id: denyBtn
                text: "Відміна"
                width: 100
                height: 50
                background: Rectangle{
                    radius: 15
                    border.width: 5
                    border.color: "#add8e6"
                }
                font.pixelSize: 16
                onClicked: {
                    logoutPopup.close()
                }
            }
            Button{
                id: agreeBtn
                text: "Вийти"
                width: 100
                height: 50
                background: Rectangle{
                    radius: 15
                    border.width: 0
                    color: "#add8e6"
                }
                font.pixelSize: 16
                onClicked: {
                    logOut()
                    logoutPopup.close()
                }
            }
        }
    }

}
