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
        leftPanel.employeeIndex = data.employeeIndex
    }

    Rectangle
    {
        id              : leftPanel
        anchors.left    : parent.left
        anchors.bottom  : parent.bottom
        height          : parent.height
        width           : parent.width/2
        border.width    : Style.popup.borderWidth
        border.color    : Style.popup.borderColor
        color           : Style.popup.backColor

        property string employeeName    : ""
        property string employeeStatus  : ""
        property int    employeeIndex   : 0
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

        Rectangle
        {
            id          : nameEmployee
            anchors.top : parent.top
            width       : parent.width
            height      : parent.height/10
            color       : Style.popup.backColor
            border.color: Style.popup.borderColor

            Text
            {
                width           : parent.width
                height          : parent.height
                text            : (leftPanel.employeeIndex+1).toString()+ ". " + leftPanel.employeeName
                      + " (" +(leftPanel.employeeStatus === "Z" ? "Zaposlenik" : "Student") + ")"
                font.pixelSize  : parent.height * 0.7
                color           : Style.popup.borderColor
                elide           : Text.ElideMiddle
            }
        }

        MButton
        {
            id                : startButton
            anchors.top       : nameEmployee.bottom
            anchors.topMargin : 20
            x                 : 20
            buttonH           : parent.height/8
            buttonW           : parent.width/2
            buttonText        : qsTr("DOLAZAK")
            textSize          : buttonH*0.6

            onClicked:
            {
                leftPanel.startTime = leftPanel.timeToInt(datetime.formatted.toString().split(" ")[0]);
                leftPanel.startDate = datetime.formatted.toString().split(" ")[0];
                startText.text = leftPanel.startDate;
                endText.text = ""
            }
        }

        MButton
        {
            id                 : leaveButton
            anchors.top        : startButton.bottom
            anchors.topMargin  : 10
            x                  : startButton.x
            buttonH            : startButton.buttonH
            buttonW            : startButton.buttonW
            buttonText         : qsTr("ODLAZAK")
            textSize           : buttonH*0.6

            onClicked:
            {
                if(leftPanel.startTime != 0)
                {
                    leftPanel.endTime = leftPanel.timeToInt(datetime.formatted.toString().split(" ")[0]) + Math.round(Math.random()*100)
                    leftPanel.endDate = datetime.formatted.toString().split(" ")[0];
                    endText.text = leftPanel.intToDate(leftPanel.endTime)

                    leftPanel.difference = leftPanel.endTime - leftPanel.startTime
                    leftPanel.startTime = 0
                    leftPanel.endTime = 0
                    workedHours.text = qsTr("ODRAĐENO: ") + leftPanel.intToDate(leftPanel.difference);
                }
            }
        }

        Text
        {
            id                      : startText
            anchors.left            : startButton.right
            anchors.top             : startButton.top
            anchors.leftMargin      : 20
            anchors.verticalCenter  : startButton.verticalCenter
            width                   : startButton.buttonW
            height                  : startButton.buttonH
            text                    : leftPanel.startDate
            color                   : Style.popup.borderColor
            font.pixelSize          : height*0.5
        }

        Text
        {
            id                      : endText
            anchors.left            : leaveButton.right
            anchors.top             : leaveButton.top
            anchors.leftMargin      : 20
            anchors.verticalCenter  : leaveButton.verticalCenter
            width                   : leaveButton.buttonW
            height                  : leaveButton.buttonH
            text                    : leftPanel.endDate
            color                   : Style.popup.borderColor
            font.pixelSize          : height*0.5
        }

        MButton
        {
            id                      : vacationButton
            anchors.bottom          : parent.bottom
            anchors.bottomMargin    : 10
            x                       : Style.popup.borderWidth*10
            buttonW                 : parent.width * 0.7
            buttonH                 : parent.height / 10
            buttonText              : qsTr("ZAHTJEV ZA GODIŠNJI")
            textSize                : buttonH*0.5
        }

        MButton
        {
            id                      : sickDayButton1
            anchors.bottom          : vacationButton.top
            anchors.bottomMargin    : 10
            x                       : Style.popup.borderWidth*10
            buttonW                 : parent.width*0.75
            buttonH                 : parent.height / 10
            buttonText              : qsTr("BOLOVANJE SA DOZVOLOM")
            textSize                : buttonH*0.5
        }

        MButton
        {

            id                      : sickDayButton2
            anchors.bottom          : sickDayButton1.top
            anchors.bottomMargin    : 10
            x                       : Style.popup.borderWidth*10
            buttonW                 : parent.width * 0.75
            buttonH                 : parent.height / 10
            buttonText              : qsTr("BOLOVANJE BEZ DOZVOLE")
            textSize                : buttonH*0.5
        }

        Text
        {
            id                      : hoursDifference
            anchors.bottom          : sickDayButton2.top
            anchors.bottomMargin    : 20
            x                       : Style.popup.borderWidth*10
            width                   : parent.width - Style.popup.borderWidth*6
            height                  : parent.height / 15
            text                    : qsTr("VIŠAK/MANJAK: ")
            color                   : Style.popup.borderColor
            font.pixelSize          : height
        }

        Text
        {
            id                      : workedHours
            anchors.bottom          : hoursDifference.top
            anchors.bottomMargin    : 15
            x                       : Style.popup.borderWidth*10
            width                   : parent.width - Style.popup.borderWidth*6
            height                  : parent.height / 15
            text                    : qsTr("ODRAĐENO: ")
            color                   : Style.popup.borderColor
            font.pixelSize          : height
        }
    }


    Rectangle
    {
        id              : rightPanel
        anchors.right   : parent.right
        anchors.bottom  : parent.bottom
        height          : parent.height
        width           : parent.width/2
        color           : Style.popup.backColor

        MClock
        {
            id                          : clock
            anchors.bottom              : exitButton.top
            anchors.horizontalCenter    : exitButton.horizontalCenter
            anchors.bottomMargin        : 5
            clockWidth                  : parent.width - Style.popup.borderWidth*6
            clockHeight                 : parent.height * 0.4
        }

        MButton
        {
            id                          : exitButton
            anchors.bottom              : monthSummary.top
            anchors.horizontalCenter    : parent.horizontalCenter
            buttonW                     : clock.width-Style.popup.borderWidth*2
            buttonH                     : parent.height * 0.15
            buttonText                  : "\u21BA"
            textSize                    : parent.height * 0.1

            onClicked:
            {
                namemodel.popupExited();
                mainPopup.close();
                keyboard.password = ""
                nameField.text = ""
            }
        }

        Rectangle
        {
            id                          : monthSummary
            anchors.horizontalCenter    : parent.horizontalCenter
            anchors.bottom              : parent.bottom
            color                       : Style.popup.backColor
            width                       : parent.width
            height                      : parent.height * 0.55
        }
    }
}
