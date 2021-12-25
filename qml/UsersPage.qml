import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQml.Models 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    RowLayout{
        id: headerRow
        height: 50
        anchors{
            top: parent.top
            topMargin: 15
            left: parent.left
            leftMargin: 15
            right: parent.right
            rightMargin: 15
        }
        ComboBox{
            id: userInteraction
            implicitWidth: 200
            implicitHeight: 50
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            model: ["Користувач", "Прибрати виділення", "Видалити"]
            font.pixelSize: 16
            delegate: ItemDelegate {
                width: userInteraction.width - 5
                anchors.horizontalCenter: parent.horizontalCenter
                contentItem: Text {
                    text: modelData

                    color: (text === "Видалити")
                        ? "red" : "black"
                    font: userInteraction.font
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
                highlighted: userInteraction.highlightedIndex === index
            }
            background: Rectangle{
                implicitWidth: 120
                implicitHeight: 40
                border.width: 5
                border.color: '#add8e6'
                radius: 5
            }

            popup: Popup{
                y: userInteraction.height - 1
                width: userInteraction.width
                implicitHeight: contentItem.implicitHeight
                padding: 1

                contentItem: ListView {
                    clip: true
                    implicitHeight: contentHeight
                    model: userInteraction.popup.visible ? userInteraction.delegateModel : null
                    currentIndex: userInteraction.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                background: Rectangle{
                    radius: 5
                    border.width: 2
                    border.color: "#8eb3bf"
                }
            }

            onCurrentIndexChanged: {
                switch(currentIndex){
                case 0:
                    return
                case 1:
                    deselectAll()
                    currentIndex = 0
                    return
                case 2:
                    currentIndex = 0
                    deleteSelected()
                }
            }
        }
        Button{
            id: newUserBtn
            implicitWidth: 170
            implicitHeight: 50
            Layout.alignment:Qt.AlignRight | Qt.AlignVCenter
            background: Rectangle{
                radius: 5
                color: '#add8e6'
            }
            Text{
                color: 'white'
                text: 'Новий користувач'
                anchors.centerIn: parent
                font.pixelSize: 16
                font.bold: true
            }

            onClicked: {
                newUserForm.open()
            }
        }
    }
    Label{
        id: legendLabel
        text: "          Username         Пароль          Ім'я              Прізвище"
        font.bold: true
        font.pixelSize: 16
        anchors.top: headerRow.bottom
        anchors.topMargin: 20
        height: 30
    }
    Label{
        text: "Посада"
        font.bold: true
        font.pixelSize: 16
        width: 100
        anchors{
            top: legendLabel.top
            right: parent.right
            rightMargin: 15
        }
    }

    ListView{
        id: userList
        model: BackendUserModel
        visible: true
        anchors{
            left: parent.left
            right: parent.right
            top: legendLabel.bottom
            bottom: parent.bottom
        }

        clip: true
        delegate: Rectangle{
            height: 50
            color: 'transparent'
            anchors{
                left: parent ? parent.left : undefined
                right: parent ? parent.right : undefined
            }

            property int fontSize: 20
            property bool fontBold: false
            property alias isChecked: checkBox.checked
            readonly property int myID: userid
            clip: true

            CheckBox{
                id: checkBox
                scale: 0.5
                indicator: Rectangle{
                    implicitWidth: 30
                    implicitHeight: 30
                    radius: 5
                    x: checkBox.leftPadding
                    y: parent.height / 2 - height / 2
                    border.color: '#add8e6'
                    border.width: 5

                    Rectangle {
                        width: 16
                        height: 16
                        x: 7
                        y: 7
                        radius: 5
                        color: checkBox.down ? "#8eb3bf" : "#add8e6"
                        visible: checkBox.checked
                    }
                }
                anchors{
                    verticalCenter: parent.verticalCenter
                }
            }

            Label{
                id: u_username
                text: username
                font.pixelSize: parent.fontSize
                font.bold: parent.fontBold
                width: 100

                anchors{
                    left: checkBox.right
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
            }
            Label{
                id: u_pass
                text: password
                font.pixelSize: parent.fontSize
                font.bold: parent.fontBold
                width: 100

                anchors{
                    left: u_username.right
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
            }
            Label{
                id: u_name
                text: BackendRepo.getUserRealName(username)
                font.pixelSize: parent.fontSize
                font.bold: parent.fontBold
                width: 100

                anchors{
                    left: u_pass.right
                    leftMargin: 5
                    verticalCenter: parent.verticalCenter
                }
            }
            Label{
                id: u_surname
                text: BackendRepo.getUserSurname(username)
                font.pixelSize: parent.fontSize
                font.bold: parent.fontBold
                width: 100

                anchors{
                    left: u_name.right
                    leftMargin: 5
                    right: u_type.left
                    rightMargin: 5
                    verticalCenter: parent.verticalCenter
                }
            }

            Label{
                id: u_type
                text: BackendRepo.getRoleName(type)
                width: 100
                font.pixelSize: parent.fontSize
                font.bold: parent.fontBold

                anchors{
                    right: parent.right
                    rightMargin: 15
                    verticalCenter: parent.verticalCenter
                }
            }
        }

        Component.onCompleted: {
        }
    }

    function deselectAll(){
        for(var child in userList.contentItem.children){
            userList.contentItem.children[child].isChecked = false
        }
    }
    function deleteSelected(){
        for(var child_iterator in userList.contentItem.children){
            let child = userList.contentItem.children[child_iterator]
            if(child.isChecked){
                BackendUserModel.deleteUser(child.myID)
                BackendUserModel.clearModel()
                BackendUserModel.loadUsers()
            }
        }
    }

    onVisibleChanged: {
        if(visible) userList.model.loadUsers()
        else userList.model.clearModel()
    }
}
