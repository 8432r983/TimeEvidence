import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import QtQuick.Controls.Styles 1.4

import EmployeeListModel 1.0
import Style 1.0

Window {
    id      : window
    width   : Style.dispWidth
    height  : Style.dispHeight
    visible : true
    title   : qsTr("Time Evidence")
    color   : Style.dispBgColor
    //visibility: Window.FullScreen;

    EmployeeListModel {id:empmodel  }
    Component.onCompleted :  empmodel.readEmployees()

    property QtObject emp  : QtObject{
        property int    ix       : -1
        property string name     : ""
        property string password : ""
        property string hours    : ""
        property string vacation : ""
        property string status   : ""
    }
    Loader {
        id       : popupLoader
        x        : 0
        y        : 0
        width    : Style.dispWidth;
        height   : Style.dispHeight;
        z        : parent.z + 10
        source   : "";
        onLoaded : item.open();
    }

    Rectangle  {
        id              : nameBox
        height          : parent.height
        width           : window.width * 0.5
        anchors.left    : parent.left
        color           : Style.popup.backColor

        ListView  {
            id                      : nameView
            width                   : parent.width - Style. popup.borderWidth * 4
            height                  : parent.height
            anchors.topMargin       : 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top             : refreshButton.bottom
            model                   : empmodel
            spacing                 : 5

            delegate: MouseArea {
                onClicked:           {
                    nameView.currentIndex = model.index;
                    emp.ix       = model.index
                    emp.name     = model.name
                    emp.password = model.password
                    emp.hours    = model.hours
                    emp.vacation = model.vacation
                    emp.status   = model.status
                }
                height  : nameView.height / 8
                width   : nameView.width

                Text  {
                    text            : (model.index + 1) + ". " + model.name
                    elide           : Text.ElideMiddle
                    font.pixelSize  : nameView.height/12
                    height          : nameView.height/8
                    width           : nameView.width
                    color           : Style.popup.borderColor
                    x               : 10
                }
            }

            highlight: Rectangle {
                color           : Style.popup.backColor
                height          : nameView.height/10
                width           : nameView.width
                radius          : Style.popup.borderRadius
                border.width    : Style.popup.borderWidth
                border.color    : Style.popup.borderColor
            }
        }

        MButton {
            id                          : refreshButton
            anchors.horizontalCenter    : parent.horizontalCenter
            anchors.top                 : parent.top
            buttonW                     : parent.width
            buttonH                     : parent.height/10
            buttonText                  : "\u27F3"
            textSize                    : buttonH
            anchors.topMargin           : 5
            onClicked                   :
            {
                empmodel.readEmployees();
                holidaycheck.loadHolidays();
            }
        }
    }

    Rectangle  {
        id              : keyboardBox
        height          : parent.height
        width           : window.width - nameBox.width
        anchors.bottom  : parent.bottom
        anchors.right   : parent.right
        color           : Style.popup.backColor

        Rectangle {
            id                          : passwordBox
            width                       : keyboard.width*0.95
            height                      : parent.height/10
            anchors.bottom              : keyboard.top
            anchors.horizontalCenter    : keyboard.horizontalCenter
            anchors.bottomMargin        : 20
            radius                      : Style.popup.borderRadius
            color                       : Style.popup.backColor
            border.color                : Style.popup.borderColor

            Text {
                id                  : nameField
                anchors.centerIn    : parent
                color               : Style.popup.borderColor
                text                : ""
                font.pixelSize      : parent.height * 0.5
            }

            MButton  {
                anchors.right           : parent.right
                anchors.verticalCenter  : parent.verticalCenter
                anchors.rightMargin     : 5
                buttonH                 : parent.height - Style.popup.borderWidth*2
                buttonW                 : parent.width/5
                buttonText              : "X"
                textSize                : buttonH * 0.7
                borderW                 : 0
                onClicked : {
                    nameField.text = ""
                    keyboard.password = ""
                }
            }
        }

        MClock {
            id: clock
            anchors.bottom              : passwordBox.top
            anchors.horizontalCenter    : passwordBox.horizontalCenter
            clockWidth                  : parent.width - Style.popup.borderWidth*2
            clockHeight                 : parent.height - passwordBox.height - keyboard.height
            border.color                : Style.popup.backColor
            border.width                : 0
        }

        NumericKeyboard  {
            id: keyboard

            property string password: ""

            width               : keyboardBox.width
            height              : keyboardBox.height * 0.5
            anchors.bottom      : parent.bottom
            buttonWidth         : keyboard.width * 0.225
            buttonHeight        : keyboard.height * 0.19
            anchors.bottomMargin: 20

            onKeyPressed: {
                if(nameField.text.length < 20) nameField.text += "\u25CF";
                password += value.toString();
            }
            onDeletePressed: {
                nameField.text = nameField.text.length > 0 ? nameField.text.slice(0, -1) : "";
                password = password.length > 0 ? password.slice(0,-1) : "";
            }
            onEnterPressed: {
                if(password === emp.password)  {
                    console.log("good Password");
                    popupLoader.setSource("qrc:/qml/EmployeeDetailPopup.qml", {"emp":emp})
                    popupLoader.loaded()
                    keyboard.password = ""
                    nameField.text    = ""
                }
                else if(emp.password === "")
                {
                    popupLoader.source = "ErrorPopup.qml";
                    popupLoader.item.message = "Niste odabrali ime.<br>Pokušajte ponovo."
                    popupLoader.loaded()
                }
                else {
                    popupLoader.source = "ErrorPopup.qml";
                    popupLoader.item.message = "Kriva lozinka.<br>Pokušajte ponovo."
                    popupLoader.loaded()
                }
            }
            onLetterPressed: {
                nameField.text += "\u25CF";
                password += letter;
            }
        }
    }
}
