import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    Label{
        id: loginLabel
        text: "Логін"
        font.pixelSize: 36
        font.bold: true
        anchors{
            top: parent.top
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }
        color: 'White'
    }
    TextField{
        id: usernameInput
        placeholderText: "Користувач"
        font.pixelSize: 16
        background: Rectangle{
            radius: 5
            border.width: 0
        }
        anchors{
            top: loginLabel.bottom
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }
        width: 250
        height: 60
    }
    TextField{
        id: passwordInput
        placeholderText: "Пароль"
        font.pixelSize: 16
        background: Rectangle{
            radius: 5
            border.width: 0
        }
        anchors{
            top: usernameInput.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        width: 250
        height: 60
        echoMode: TextInput.Password
    }
    Button{
        id: revealPassword
        text: "👁"
        scale: 1.5
        background: Rectangle{
            color: 'transparent'
        }
        anchors{
            right: passwordInput.right
            rightMargin: 10
            verticalCenter: passwordInput.verticalCenter
        }
        onClicked: {
            passwordInput.echoMode =
                    (passwordInput.echoMode === TextInput.Password)
                    ? TextInput.Normal : TextInput.Password
        }
    }

    Label{
        id: registerLabel
        text: "В мене немає аккаунту"
        font.underline: true
        anchors{
            top: passwordInput.bottom
            topMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                contactAdminPopup.open()
            }
            cursorShape: "PointingHandCursor"
        }
    }
    Popup{
        id: contactAdminPopup
        width: 400
        height: 100
        anchors.centerIn: parent
        background: Rectangle{
            radius: 5
            border.width: 0
        }

        Text{
            anchors.fill: parent

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text: "Для реєстрації нового акаунту зверніться до адміністратора"
            font.pixelSize: 20
            wrapMode: Text.Wrap
        }
        dim: true
    }
    Button{
        id: connectBtn
        width: 150
        height: 60
        anchors{
            top: registerLabel.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        text: "Увійти"
        background: Rectangle{
            radius: 5
            border.width: 0
        }
        font.pixelSize: 16

        onClicked: {
            BackendRepo.authUser(usernameInput.text, passwordInput.text)
            usernameInput.clear()
            passwordInput.clear()
        }
    }

    focus: true
    Keys.onPressed: {
        if(event.key === Qt.Key_Return)
            connectBtn.clicked()
    }
}
