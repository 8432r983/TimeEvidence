import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Style 1.0

import MonthModel 1.0
import MonthLogger 1.0

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
    property var emp;
    Component.onCompleted: {
        leftPanel.employeeName = emp.name;
        leftPanel.employeeStatus = emp.status;

        vacationData.leftoverhours = emp.hours
        vacationData.vacationdays = emp.vacation

        monthmodel.loadEntries(datetime.formatted.toString().split(" ")[1], leftPanel.employeeName);

        leftPanel.buttonsEnabled = activity.getActivity(leftPanel.employeeName) !== "";
    }

    MonthLogger { id: monthlogger }

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
            width           : parent.width * 0.5
            color           : Style.popup.backColor

            property string employeeName    : ""
            property string employeeStatus  : ""
            property string startTime       : ""
            property string endTime         : ""
            property bool buttonsEnabled    : activity.getActivity(leftPanel.employeeName) !== ""

            function intToTime(minutes)
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

            Column
            {
                id              : buttonsColumn
                spacing         : 10
                width           : parent.width * 0.5
                height          : parent.height
                anchors.left    : parent.left

                MButton
                {
                    id                          : travelButton
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("SATI PUTA")
                    textSize                    : buttonH*0.5
                }
                MButton
                {
                    id                          : vacationButton
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("ZAHTJEV ZA GODIŠNJI")
                    textSize                    : buttonH*0.4
                }
                MButton
                {
                    id                          : sickDayButton1
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("BOLOVANJE SA DOZVOLOM")
                    textSize                    : parent.height * 0.07
                }
                MButton
                {

                    id                          : sickDayButton2
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("BOLOVANJE BEZ DOZVOLE")
                    textSize                    : parent.height * 0.07
                }
                MButton
                {
                    id                          : exitButton
                    buttonW                     : parent.width
                    buttonH                     : parent.height * 0.17
                    buttonText                  : "\u2B8C"
                    textSize                    : parent.height * 0.15
                    onClicked                   : mainPopup.close();
                }
            }

            Column
            {
                id                  : vacationData
                width               : parent.width - buttonsColumn.width
                height              : parent.height
                anchors.right       : parent.right

                property string leftoverhours   : ""
                property string vacationdays    : ""

                MText
                {
                    id                  : leftoverHours
                    width               : parent.width
                    height              : parent.height * 0.5
                    mainText            : "Višak sati:\n" + vacationData.leftoverhours
                    textH               : parent.height * 0.18
                    border.width        : 0
                }
                MText
                {
                    id                  : vacationDays
                    width               : parent.width
                    height              : parent.height * 0.5
                    mainText            : "Godišnji\nodmor:\n" + vacationData.vacationdays + " dana"
                    textH               : parent.height * 0.18
                    border.width        : 0
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
                    text           : leftPanel.employeeName
                    font.pixelSize : parent.height * 0.7
                    color          : Style.popup.borderColor
                    elide          : Text.ElideMiddle
                }

                Text
                {
                    x                       : parent.width - paintedWidth*2
                    text                    : leftPanel.employeeStatus === "Z" ? "Z" : "S"
                    color                   : Style.popup.borderColor
                    anchors.verticalCenter  : parent.verticalCenter
                    font.pixelSize          : parent.height * 0.7
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
                    enabled                     : !leftPanel.buttonsEnabled
                    opacity                     : !leftPanel.buttonsEnabled ? 1.0 : 0.3

                    onClicked:
                    {
                        leftPanel.startTime = datetime.formatted.toString().split(" ")[0];
                        activity.setActivity(leftPanel.employeeName, leftPanel.startTime);
                        leftPanel.buttonsEnabled = activity.getActivity(leftPanel.employeeName) !== "";
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
                    enabled                 : leftPanel.buttonsEnabled
                    opacity                 : leftPanel.buttonsEnabled ? 1.0 : 0.3

                    onClicked:
                    {
                        //leftPanel.endTime = datetime.formatted.toString().split(" ")[0];
                        leftPanel.endTime = leftPanel.intToTime(leftPanel.timeToInt(datetime.formatted.toString().split(" ")[0]) + Math.round(Math.random() * 100));

                        if(activity.getActivity(leftPanel.employeeName) !== "")
                        {
                            monthlogger.addEntry(leftPanel.employeeName, datetime.currentDay.slice(0,3),
                                                 datetime.formatted.toString().split(" ")[1],
                                                 activity.getActivity(leftPanel.employeeName),
                                                 leftPanel.endTime, "-", "-", "-", "-");


                            activity.setActivity(leftPanel.employeeName, "");
                        }

                        leftPanel.buttonsEnabled = activity.getActivity(leftPanel.employeeName) !== "";

                        monthmodel.loadEntries(datetime.formatted.toString().split(" ")[1], leftPanel.employeeName);
                    }
                }
            }
        }
    }

    Rectangle
    {
        property int childrenWidth: parent.width/9

        id                          : bottomPanel
        width                       : parent.width
        height                      : parent.height - topPanel.height
        anchors.top                 : topPanel.bottom
        anchors.topMargin           : 10
        anchors.horizontalCenter    : topPanel.horizontalCenter
        color                       : Style.popup.backColor

        MonthModel {id: monthmodel}

        Row
        {
            id          : headerRow
            height      : parent.height/8
            anchors.top : bottomPanel.top

            MText
            {
                id: day
                mainText            : "Dan"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false
            }
            MText
            {
                id: clockIn
                mainText            : "Dolazak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                id: clockOut
                mainText            : "Odlazak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                id: total
                mainText            : "Sat"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                id: difference
                mainText            : "Višak Manjak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                id: travel
                mainText            : "Putni sat"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false
            }
            MText
            {
                id: holiday
                mainText            : "Praznik"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false
            }
            MText
            {
                id: sickday
                mainText            : "Bolovanje"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false
            }
            MText
            {
                id: vacation
                mainText            : "Godišnji"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false
            }
        }

        ListView
        {
            id          : hoursStats
            width       : parent.width
            height      : parent.height - headerRow.height
            anchors.top : headerRow.bottom
            model       : monthmodel
            delegate    : Row
            {
                height  : hoursStats.height/5

                MText
                {
                    mainText: model.date
                    textH   : parent.height
                    width   : day.width
                }
                MText
                {
                    mainText: model.clockIn
                    textH   : parent.height
                    width   : clockIn.width
                }
                MText
                {
                    mainText: model.clockOut
                    textH   : parent.height
                    width   : clockOut.width
                }
                MText
                {
                    mainText: model.total
                    textH   : parent.height
                    width   : total.width
                }
                MText
                {
                    mainText: model.difference
                    textH   : parent.height
                    width   : difference.width
                }
                MText
                {
                    mainText: model.travel
                    textH   : parent.height
                    width   : travel.width
                }
                MText
                {
                    mainText: model.holiday
                    textH   : parent.height
                    width   : holiday.width
                }
                MText
                {
                    mainText: model.sickday
                    textH   : parent.height
                    width   : sickday.width
                }
                MText
                {
                    mainText: model.vacation
                    textH   : parent.height
                    width   : vacation.width
                }
            }
        }
    }
}
