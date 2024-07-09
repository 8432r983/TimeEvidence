import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Style 1.0

Popup
{
    id                  : mainPopup
    height              : parent.height
    width               : parent.width
    anchors.centerIn    : parent
    background          : Rectangle
    {
        color: Style.popup.backColor
    }

    function setData(data)
    {
        leftPanel.employeeName = data.employeeName
        leftPanel.employeeStatus = data.employeeStatus
    }

    Rectangle
    {
        id           : topPanel
        width        : parent.width
        height       : parent.height * 0.5
        border.width : Style.popup.borderWidth

        Rectangle
        {
            id              : leftPanel
            x               : Style.popup.borderWidth
            y               : Style.popup.borderWidth
            height          : parent.height-Style.popup.borderWidth*2
            width           : parent.width * 0.4
            color           : Style.popup.backColor

            property string employeeName    : ""
            property string employeeStatus  : ""
            property int    startTime       : 0
            property int    endTime         : 0
            property int    difference      : 0
            property string startDate       : ""
            property string endDate         : ""

            function intToDate(minutes)
            {
                let Hours = Math.floor(minutes/60);
                let Minutes = minutes%60;

                let HoursStr = "";
                let MinutesStr = "";

                if(Hours < 10) HoursStr = "0" + Hours.toString();
                else HoursStr = Hours.toString();

                if(Minutes < 10) MinutesStr = "0" + Minutes.toString();
                else MinutesStr = Minutes.toString();

                return HoursStr + ":" + MinutesStr;
            }

            function timeToInt(time)
            {
                let Hours = Math.floor(time.split(":")[0]) * 60
                let Minutes = Math.floor(time.split(":")[1])
                return Hours + Minutes
            }

            MButton
            {
                id                          : vacationButton
                anchors.horizontalCenter    : exitButton.horizontalCenter
                anchors.bottom              : sickDayButton1.top
                anchors.bottomMargin        : 10
                buttonW                     : exitButton.buttonW
                buttonH                     : exitButton.buttonH
                buttonText                  : qsTr("ZAHTJEV ZA GODIŠNJI")
                textSize                    : buttonH*0.5
            }

            MButton
            {
                id                          : sickDayButton1
                anchors.horizontalCenter    : exitButton.horizontalCenter
                anchors.bottom              : sickDayButton2.top
                anchors.bottomMargin        : 10
                buttonW                     : exitButton.buttonW
                buttonH                     : exitButton.buttonH
                buttonText                  : qsTr("BOLOVANJE SA DOZVOLOM")
                textSize                    : buttonH*0.5
            }

            MButton
            {

                id                          : sickDayButton2
                anchors.horizontalCenter    : exitButton.horizontalCenter
                anchors.bottom              : exitButton.top
                anchors.bottomMargin        : 10
                buttonW                     : exitButton.buttonW
                buttonH                     : exitButton.buttonH
                buttonText                  : qsTr("BOLOVANJE BEZ DOZVOLE")
                textSize                    : buttonH*0.5
            }

            MButton
            {
                id                          : exitButton
                anchors.bottom              : leftPanel.bottom
                anchors.horizontalCenter    : leftPanel.horizontalCenter
                buttonW                     : leftPanel.width-Style.popup.borderWidth*2
                buttonH                     : parent.height * 0.2125
                buttonText                  : "\u2B8C"
                textSize                    : parent.height * 0.15

                onClicked:
                {
                    namemodel.popupExited();
                    mainPopup.close();
                    keyboard.password = ""
                    nameField.text = ""
                }
            }
        }

        Rectangle
        {
            id                  : rightPanel
            width               : parent.width - leftPanel.width - Style.popup.borderWidth*2
            height              : parent.height - Style.popup.borderWidth*2
            y                   : Style.popup.borderWidth
            anchors.left        : leftPanel.right
            anchors.top         : leftPanel.top
            color               : Style.popup.backColor

            Rectangle
            {
                id                      : nameEmployee
                anchors.bottom          : parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width                   : parent.width - Style.popup.borderWidth*4
                height                  : parent.height * 0.15
                color                   : Style.popup.backColor
                border.color            : Style.popup.borderColor

                Text
                {
                    x              : parent.width/2 - paintedWidth/2
                    width          : parent.width
                    height         : parent.height
                    text           : leftPanel.employeeName + " (" +(leftPanel.employeeStatus === "Z" ? "Z" : "S") + ")"
                    font.pixelSize : parent.height * 0.7
                    color          : Style.popup.borderColor
                    elide          : Text.ElideMiddle
                }
            }

            MClock
            {
                id                          : clock
                anchors.bottom              : startAndLeave.top
                anchors.horizontalCenter    : startAndLeave.horizontalCenter
                clockWidth                  : parent.width - Style.popup.borderWidth*2
                clockHeight                 : parent.height * 0.8
            }

            Rectangle
            {
                id: startAndLeave
                anchors.bottom: nameEmployee.top
                anchors.horizontalCenter: nameEmployee.horizontalCenter
                width: parent.width
                height: parent.height * 0.25
                color: Style.popup.backColor

                MButton
                {
                    id                          : startButton
                    anchors.top                 : parent.top
                    anchors.left                : parent.left
                    anchors.leftMargin          : Style.popup.borderWidth*2
                    anchors.verticalCenter      : parent.verticalCenter
                    buttonH                     : parent.height - Style.popup.borderWidth*4
                    buttonW                     : parent.width * 0.5 - Style.popup.borderWidth*4
                    buttonText                  : qsTr("DOLAZAK")
                    textSize                    : buttonH*0.6

                    onClicked:
                    {
                        leftPanel.startTime = leftPanel.timeToInt(datetime.formatted.toString().split(" ")[0]);
                        leftPanel.startDate = datetime.formatted.toString().split(" ")[0];
                        console.log(leftPanel.startDate, leftPanel.startTime)
                    }
                }

                MButton
                {
                    id                      : leaveButton
                    anchors.left            : startButton.right
                    anchors.leftMargin      : Style.popup.borderWidth*4
                    anchors.bottom          : startButton.bottom
                    anchors.verticalCenter  : startButton.verticalCenter
                    buttonH                 : startButton.buttonH
                    buttonW                 : startButton.buttonW
                    buttonText              : qsTr("ODLAZAK")
                    textSize                : buttonH*0.6

                    onClicked:
                    {
                        if(leftPanel.startTime != 0)
                        {
                            leftPanel.endTime = leftPanel.timeToInt(datetime.formatted.toString().split(" ")[0]) + Math.round(Math.random()*100)
                            leftPanel.endDate = datetime.formatted.toString().split(" ")[0];

                            leftPanel.difference = leftPanel.endTime - leftPanel.startTime
                            leftPanel.startTime = 0
                            leftPanel.endTime = 0

                            console.log(leftPanel.endDate, leftPanel.endTime);
                            console.log(leftPanel.difference)
                        }
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: bottomPanel
    }
}
