import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: root
    anchors.centerIn: parent
    dim: true
    focus: true
    padding: 15
    width: 500
    height: 480
    background: Rectangle{
        radius: 5
        color: 'white'
    }

    Column{
        anchors.fill: parent
        anchors.centerIn: parent
        Label{
            id: userLabel
            text: 'Новий користувач'
        }
        TextField{
            id: usernameInput
            placeholderText: "Ім'я користувача"
        }
        TextField{
            id: passwordInput
            placeholderText: "Пароль"
        }
        TextField{
            id: passwordRepeatInput
            placeholderText: "Повторно пароль"
        }
        Button{
            id: nextBtn
            width: 100
            height: 50
            enabled: (usernameInput.text.length &&
                      passwordInput.text.length &&
                      passwordRepeatInput.text === passwordInput.text &&
                      !BackendRepo.userExists(usernameInput.text))
            background: Rectangle{
                radius: 5
                color: '#add8e6'
            }
            Text{
                color: 'white'
                text: 'Далі'
                anchors.centerIn: parent
                font.pixelSize: 20
                font.bold: true
            }
            onClicked: {
                newWorkerForm.open()
            }
        }
    }
    function createNewUser(type, workerID){
        BackendRepo.createUser(usernameInput.text,
                               passwordInput.text,
                               type, workerID)
        root.close()
    }

    onClosed: {
        usernameInput.clear()
        passwordInput.clear()
        passwordRepeatInput.clear()
        BackendUserModel.reloadUsers()
    }
}
