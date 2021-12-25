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
    property bool buttonEnabled:  (nameInput.text.length &&
                                  surnameInput.text.length &&
                                  patronymicInput.text.length &&
                                  phoneInput.text.length &&
                                  salaryInput.text.length &&
                                  roleBox.currentIndex
                                  )
    Column{
        anchors.fill: parent
        anchors.centerIn: parent
        Label{
            id: workerLabel
            text: 'Новий працівник'
        }
        TextField{
            id: nameInput
            placeholderText: "Ім'я"
        }
        TextField{
            id: surnameInput
            placeholderText: "Прізвище"
        }
        TextField{
            id: patronymicInput
            placeholderText: "По-батькові"
        }
        TextField{
            id: phoneInput
            placeholderText: "Телефон"
        }
        TextField{
            id: salaryInput
            placeholderText: "Зар. плата"
        }
        ComboBox{
            id: warehouseBox
            property int currentWarehouseIndex
            model: ListModel{
                id: warehouseModel
            }

            Component.onCompleted: {
                let warehouseNames = BackendRepo.getAllWarehouseNames()
                let warehouseIDs = BackendRepo.getAllWarehouseIDs()

                for(var id in warehouseNames){
                    warehouseModel.append({text: warehouseNames[id]})
                }
            }
            onCurrentIndexChanged: {
                let warehouseNames = BackendRepo.getAllWarehouseNames()
                let warehouseIDs = BackendRepo.getAllWarehouseIDs()

                for(var id in warehouseNames){
                    if(warehouseModel.get(currentIndex) &&
                            warehouseNames[id] === warehouseModel.get(currentIndex).text)
                    {
                        currentWarehouseIndex = warehouseIDs[id]
                    }
                }
            }
        }
        ComboBox{
            id: roleBox
            property int currentRoleIndex
            model: ListModel{
                id: roleModel
            }
            Component.onCompleted: {
                let roleNames = BackendRepo.getAllRoleNames()
                let roleIDs = BackendRepo.getAllRoleIDs()

                for(var id in roleNames){
                    roleModel.append({text: roleNames[id]})
                }
            }
            onCurrentIndexChanged: {
                let roleNames = BackendRepo.getAllRoleNames()
                let roleIDs = BackendRepo.getAllRoleIDs()

                for(var id in roleNames){
                    if(roleModel.get(currentIndex) &&
                            roleNames[id] === roleModel.get(currentIndex).text)
                    {
                        currentRoleIndex = roleIDs[id]
                    }
                }
            }
        }

        Button{
            id: createBtn
            width: 100
            height: 50
            enabled: buttonEnabled
            background: Rectangle{
                radius: 5
                color: '#add8e6'
            }
            Text{
                color: 'white'
                text: 'Готово'
                anchors.centerIn: parent
                font.pixelSize: 20
                font.bold: true
            }
            onClicked: {
                var lastID = BackendRepo.lastWorkerID()
                BackendRepo.createWorker(lastID + 1, nameInput.text,
                                 surnameInput.text,
                                 patronymicInput.text,
                                 phoneInput.text,
                                 salaryInput.text,
                                 warehouseBox.currentWarehouseIndex,
                                 roleBox.currentRoleIndex)
                root.close()
                workerToUser(roleBox.currentRoleIndex
                             ,lastID + 1)
            }
        }
    }
    onClosed: {
        nameInput.clear()
        surnameInput.clear()
        patronymicInput.clear()
        phoneInput.clear()
        salaryInput.clear()
        roleModel.clear()
        warehouseModel.clear()
    }
}
