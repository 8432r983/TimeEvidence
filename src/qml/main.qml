import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3
import NameListModel 1.0

import QtQuick.Controls.Styles 1.4
import Style 1.0

Window
{
    id      : window
    width   : Style.dispWidth
    height  : Style.dispHeight
    visible : true
    title   : qsTr("Time Evidence")
    color   : Style.dispBgColor

    NameListModel {id:namemodel}

    Rectangle
    {
        id              : nameBox
        height          : parent.height
        width           : window.width * 0.4
        anchors.left    : parent.left
        color           : Style.popup.backColor

        ListView
        {
            id                      : nameView
            width                   : parent.width-Style.popup.borderWidth*4
            height                  : parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            model                   : namemodel
            spacing                 : 5

            delegate: MouseArea
            {
                onClicked:
                {
                    nameView.currentIndex = index;
                    keyboard.name = namemodel.getName(index);
                    keyboard.employeeStatus = namemodel.getStatus(index);
                    keyboard.employeeIndex = index;

                    //console.log(keyboard.name);
                    //console.log(keyboard.employeeStatus);
                }
                height: nameView.height/8
                width: parent.width

                Text
                {
                    text            : (index+1).toString() + ". " + model.name
                    elide           : Text.ElideMiddle
                    font.pixelSize  : nameView.height/12
                    height          : nameView.height/8
                    width           : nameView.width
                    color           : Style.popup.borderColor
                }
            }

            highlight: Rectangle {
                color           : Style.popup.backColor
                height          : nameView.height/10
                width           : parent.width
                radius          : Style.popup.borderRadius
                border.width    : Style.popup.borderWidth
                border.color    :Style.popup.borderColor
            }
        }
    }

    Rectangle
    {
        id              : keyboardBox
        height          : parent.height
        width           : window.width - nameBox.width
        anchors.bottom  : parent.bottom
        anchors.right   : parent.right
        border.width    : Style.popup.borderWidth
        color           : Style.popup.backColor
        border.color    : Style.popup.borderColor

        Rectangle
        {
            id                          : passwordBox
            width                       : keyboard.width*0.95
            height                      : parent.height/10
            anchors.bottom              : keyboard.top
            anchors.horizontalCenter    : keyboard.horizontalCenter
            anchors.bottomMargin        : 20
            radius                      : Style.popup.borderRadius
            color                       : Style.popup.backColor
            border.color                : Style.popup.borderColor

            Text
            {
                id                  : nameField
                anchors.centerIn    : parent
                color               : Style.popup.borderColor
                text                : ""
                font.pixelSize      : parent.height * 0.5
            }

            MButton
            {
                anchors.right           : parent.right
                anchors.verticalCenter  : parent.verticalCenter
                anchors.rightMargin     : 5
                buttonH                 : parent.height - Style.popup.borderWidth*2
                buttonW                 : parent.width/5
                buttonText              : "X"
                textSize                : buttonH * 0.7
                borderW                 : 0

                onClicked:
                {
                    nameField.text = ""
                    keyboard.password = ""
                }
            }
        }

        MClock
        {
            anchors.bottom              : passwordBox.top
            anchors.horizontalCenter    : passwordBox.horizontalCenter
            clockWidth                  : parent.width-Style.popup.borderWidth*2
            clockHeight                 : parent.height - passwordBox.height - keyboard.height
            border.color                : Style.popup.backColor
            border.width                : 0
        }

        NumericKeyboard {
            id: keyboard

            property string password: "1456A"
            property string name: namemodel.getName(0);
            property string employeeStatus: namemodel.getStatus(0);
            property int    employeeIndex: 0

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
                console.log("Entered: " + nameField.text);
                if(namemodel.verifyEmployee(password, name))
                {
                    mainPopup.setData({employeeName: name, employeeStatus: employeeStatus, employeeIndex: employeeIndex});
                    mainPopup.open()
                    //leftPanel.employeeName = name;
                    //leftPanel.employeeStatus = employeeStatus;
                    //leftPanel.employeeIndex = employeeIndex;
                }
            }
            onLetterPressed: {
                nameField.text += "\u25CF";
                password += letter;
            }
        }
    }

    EmployeeDetailPopup
    {
        id: mainPopup
    }
}
