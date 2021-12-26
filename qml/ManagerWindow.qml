import QtQuick 2.15
import QtQuick.Controls 2.15

MainWindow{
    id: root
    property string selectedBtn: ""
    property string userName: ""
    Label{
        id: headingLabel
        width: 150
        height: 40
        text: userName
        anchors{
            left: parent.left
            top: parent.top
        }
        font.pixelSize: 16
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        MouseArea{
            id: mousearea
            anchors.fill: parent
            hoverEnabled: true
        }

        ToolTip.visible: mousearea.containsMouse
        ToolTip.text: 'Manager'
    }

    Column{
        width: 150
        anchors{
            left: parent.left
            top: headingLabel.bottom
        }

        Button{
            id: warehousesBtn
            width: parent.width
            height: 50
            text: "Склади"
            font.pixelSize: 16
            font.bold: true
            contentItem: Text{
                text: parent.text
                font: parent.font
                color: (selectedBtn === parent.text)
                        ? 'black' : 'white'
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle{
                color: (selectedBtn === parent.text)
                     ? 'white' : '#add8e6'
            }

            onClicked: {
                selectedBtn = warehousesBtn.text
            }
        }
        Button{
            id: goodsBtn
            width: parent.width
            height: 50
            text: "Товари"
            font.bold: true
            font.pixelSize: 16
            contentItem: Text{
                text: parent.text
                font: parent.font
                color: (selectedBtn === parent.text)
                       ? 'black' : 'white'
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle{
                color: (selectedBtn === parent.text)
                    ? 'white' : '#add8e6'
            }

            onClicked: {
                selectedBtn = goodsBtn.text
            }
        }
    }
    Rectangle{
        id: mainArea
        color: 'white'
        anchors{
            left: headingLabel.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        UsersPage{
            id: usersPage
            anchors.fill: parent
            anchors{
                leftMargin: 15
                rightMargin: 15
            }

            visible: selectedBtn === "Користувачі"
        }
        NewWorkerForm{
            id: newWorkerForm
            function workerToUser(roleID, workerID){
                newUserForm.createNewUser(roleID, workerID)
            }
        }
    }
}
