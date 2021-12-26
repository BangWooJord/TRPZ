import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    RowLayout{
        id: headerRow
        height: 50
        spacing: 0
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
            implicitWidth: 180
            implicitHeight: 40
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
        ComboBox{
            id: sortBox
            implicitWidth: 140
            implicitHeight: 40
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            model: ["Сортувати", "За ім'ям a-z", "За ім'ям z-a",
                "За посадою ↑", "За посадою ↓"]
            font.pixelSize: 16
            delegate: ItemDelegate {
                width: userInteraction.width - 5
                anchors.horizontalCenter: parent.horizontalCenter
                contentItem: Text {
                    text: modelData

                    color: 'black'
                    font: sortBox.font
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                highlighted: sortBox.highlightedIndex === index
            }
            background: Rectangle{
                implicitWidth: 120
                implicitHeight: 40
                border.width: 5
                border.color: '#add8e6'
                radius: 5
            }

            popup: Popup{
                y: sortBox.height - 1
                width: sortBox.width
                implicitHeight: contentItem.implicitHeight
                padding: 1

                contentItem: ListView {
                    clip: true
                    implicitHeight: contentHeight
                    model: sortBox.popup.visible ? sortBox.delegateModel : null
                    currentIndex: sortBox.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                background: Rectangle{
                    radius: 5
                    border.width: 2
                    border.color: "#8eb3bf"
                }
            }

            onCurrentIndexChanged: {
                if(!currentIndex) return
                else BackendUserModel.sortUsers(currentIndex - 1)
            }
        }
        Button{
            id: filterBtn
            implicitWidth: 140
            implicitHeight: 40
            Layout.alignment:Qt.AlignLeft | Qt.AlignVCenter
            background: Rectangle{
                radius: 5
                border.width: 2
                border.color: '#add8e6'
            }
            Text{
                text: 'Фільтри'
                anchors.centerIn: parent
                font.pixelSize: 16
                font.bold: true
            }

            onClicked: {
                filterPopup.open()
            }
        }
        Button{
            id: newUserBtn
            implicitWidth: 170
            implicitHeight: 50
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            background: Rectangle{
                radius: 5
                color: '#57b1cf'
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

    Popup{
        id: filterPopup
        anchors.centerIn: parent
        width: 320
        height: 480
        background: Rectangle{
            radius: 5
            border.width: 5
            border.color: '#add8e6'
        }
        Column{
            height: 320
            anchors{
                centerIn: parent
                left: parent.left
                right: parent.right
            }
            Label{
                text: 'За username'
                font.pixelSize: 16
                font.bold: true
                anchors{
                    left: parent.left
                    right: parent.right
                }
                horizontalAlignment: Text.AlignHCenter
            }
            ListView{
                id: usernameList
                anchors{
                    left: parent.left
                    right: parent.right
                }

                height: 100
                model: ListModel{
                    id: usernameListModel
                }
                clip: true
                delegate: Rectangle{
                    property alias text: checkboxText.text
                    property alias checked: checkbox.checked
                    clip: true
                    anchors{
                        left: (parent) ? parent.left : undefined
                        right: (parent) ? parent.right : undefined
                    }
                    height: 30
                    Row{
                        anchors.fill: parent

                        CheckBox{
                            id: checkbox
                            scale: 0.5
                            indicator: Rectangle{
                                implicitWidth: 30
                                implicitHeight: 30
                                radius: 5
                                x: checkbox.leftPadding
                                y: parent.height / 2 - height / 2
                                border.color: '#add8e6'
                                border.width: 5

                                Rectangle {
                                    width: 16
                                    height: 16
                                    x: 7
                                    y: 7
                                    radius: 5
                                    color: checkbox.down ? "#57b1cf" : "#add8e6"
                                    visible: checkbox.checked
                                }
                            }
                            anchors{
                                verticalCenter: parent.verticalCenter
                            }
                        }
                        Text{
                            id: checkboxText
                            text: textValue
                            font.pixelSize: 16
                            anchors{
                                verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                }
            }
            Label{
                text: 'За оплатою'
                font.pixelSize: 16
                font.bold: true
                anchors{
                    left: parent.left
                    right: parent.right
                    topMargin: 15
                }
                horizontalAlignment: Text.AlignHCenter
            }

            RangeSlider{
                id: salaryRangeSlider
                width: filterPopup.width/1.5

                first.handle: Rectangle {
                    x: salaryRangeSlider.leftPadding + salaryRangeSlider.first.visualPosition * (salaryRangeSlider.availableWidth - width)
                    y: salaryRangeSlider.topPadding + salaryRangeSlider.availableHeight / 2 - height / 2
                    implicitWidth: 26
                    implicitHeight: 26
                    radius: 13
                    color: salaryRangeSlider.first.pressed ? "#57b1cf" : "#add8e6"
                    border.width: 0
                }

                second.handle: Rectangle {
                    x: salaryRangeSlider.leftPadding + salaryRangeSlider.second.visualPosition * (salaryRangeSlider.availableWidth - width)
                    y: salaryRangeSlider.topPadding + salaryRangeSlider.availableHeight / 2 - height / 2
                    implicitWidth: 26
                    implicitHeight: 26
                    radius: 13
                    color: salaryRangeSlider.second.pressed ? "#57b1cf" : "#add8e6"
                    border.width: 0
                }
                TextInput{
                    text: Math.round(parent.first.value * 10)/10
                    font.pixelSize: 16
                    font.bold: true
                    width: 50
                    anchors{
                        left: parent.left
                        top: parent.bottom
                        topMargin: 5
                    }
                    onTextEdited: {
                        if(!salaryRangeSlider.first.pressed)
                            parent.first.value = text
                    }
                    horizontalAlignment: Text.AlignHCenter
                }
                TextInput{
                    text: Math.round(parent.second.value * 10)/10
                    width: 50
                    font.pixelSize: 16
                    font.bold: true
                    anchors{
                        right: parent.right
                        top: parent.bottom
                        topMargin: 5
                    }
                    onTextEdited: {
                        if(!salaryRangeSlider.second.pressed)
                            parent.second.value = text
                    }
                    horizontalAlignment: Text.AlignHCenter
                }

                Component.onCompleted: {
                    let salaries = BackendUserModel.getAllSalaries()
                    var min = salaries[0]
                    var max = salaries[0]
                    for(var i in salaries){
                        if(min > salaries[i]) min = salaries[i]
                        if(max < salaries[i]) max = salaries[i]
                    }

                    salaryRangeSlider.from = min
                    salaryRangeSlider.first.value = min
                    salaryRangeSlider.to = max
                    salaryRangeSlider.second.value = max
                }
            }
        }

        Button{
            id: applyFiltersBtn
            width: 170
            height: 50
            background: Rectangle{
                radius: 5
                color: '#57b1cf'
            }
            anchors{
                bottom: parent.bottom
                bottomMargin: 15
                horizontalCenter: parent.horizontalCenter
            }
            Text{
                color: 'white'
                text: 'Застосувати'
                anchors.centerIn: parent
                font.pixelSize: 16
                font.bold: true
            }

            onClicked: {
                let filters = []
                if(getUsernameFilters())
                    filters.push(getUsernameFilters())
                BackendUserModel.loadFilteredUsers(filters)
                filterPopup.close()
            }
            function getUsernameFilters(){
                let usernameFilters = ""
                for(var i in usernameList.contentItem.children){
                    if(usernameList.contentItem.children[i].text &&
                            usernameList.contentItem.children[i].checked){
                        usernameFilters += " Username LIKE '" +
                            usernameList.contentItem.children[i].text + "%' OR"
                    }
                }
                if(usernameFilters === "Username LIKE") return
                usernameFilters = usernameFilters.substring(0, usernameFilters.length - 2)
                return usernameFilters
            }
        }
        onOpened: {
            let chars = BackendUserModel.getNCharsOf("Username", 1)
            chars = chars.filter(onlyUnique)
            for(var i in chars){
                usernameListModel.append({textValue: chars[i]})
            }
        }
        onClosed: {
            usernameListModel.clear()
        }

        function onlyUnique(value, index, self) {
          return self.indexOf(value) === index;
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
            rightMargin: 25
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
                        color: checkBox.down ? "#57b1cf" : "#add8e6"
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
                    rightMargin: 25
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
