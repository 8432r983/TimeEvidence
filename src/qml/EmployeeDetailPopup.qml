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
                let Hours = Math.floor(Math.abs(minutes)/60);
                let Minutes = Math.abs(minutes)%60;

                let HoursStr = "";
                let MinutesStr = "";

                if(Hours < 10) HoursStr = "0" + Hours.toString();
                else HoursStr = Hours.toString();

                if(Minutes < 10) MinutesStr = "0" + Minutes.toString();
                else MinutesStr = Minutes.toString();

                let res = HoursStr + ":" + MinutesStr

                if(minutes < 0)
                    res = "-" + res

                return res;
            }

            function timeToInt(time)
            {
                let Hours = Math.floor(time.replace("-","").split(":")[0]) * 60
                let Minutes = Math.floor(time.replace("-","").split(":")[1])

                if(time[0] === "-")
                    return -(Hours + Minutes)

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
                    buttonText                  : qsTr("ZAHTJEV ZA GO")
                    textSize                    : buttonH*0.5
                }
                MButton
                {
                    id                          : sickDayButton1
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("BOLOVANJE SA DOZ")
                    textSize                    : parent.height * 0.08
                }
                MButton
                {

                    id                          : sickDayButton2
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("BOLOVANJE BEZ DOZ")
                    textSize                    : parent.height * 0.08
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
                    mainText            : qsTr("Višak sati:<br><b>" + vacationData.leftoverhours)
                    textH               : parent.height * 0.18
                }
                MText
                {
                    id                  : vacationDays
                    width               : parent.width
                    height              : parent.height * 0.5
                    mainText            : qsTr("Godišnji<br>odmor:<br><b>" + vacationData.vacationdays + "</b><br>dana")
                    textH               : parent.height * 0.18
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
                        // THESE LINES ARE USED TO TOGGLE THE RANDOMNESS THAT IS INPUTED IN THE TABLE
                        // IF DON'T WANT TO ADD RANDOM AMOUNT OF TIME TO THE INPUT THEN USE THE LINE UNDER
                        // ELSE USE THE LINE UNDER THAT ONE TO ADD SOME RANDOM TIME TO THE INPUT

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

                        totalSum.mainText = monthmodel.getTotalSum();
                        differenceSum.mainText = monthmodel.getDifferenceSum();
                        travelSum.mainText = monthmodel.getTravelSum();
                        holidaySum.mainText = monthmodel.getHolidaySum();
                        sickdaySum.mainText = monthmodel.getSickdaySum();
                        vacationSum.mainText = monthmodel.getVacationSum();
                    }
                }
            }
        }
    }

    Rectangle
    {
        property var childrenWidth: [parent.width * 0.05,
                                     parent.width * 1/9,
                                     parent.width * 1/9,
                                     parent.width * 1/9,
                                     parent.width * (2/9 -0.05),
                                     parent.width * 1/9,
                                     parent.width * 1/9,
                                     parent.width * 1/9,
                                     parent.width * 1/9]

        id                          : bottomPanel
        width                       : parent.width
        height                      : parent.height - topPanel.height
        anchors.top                 : topPanel.bottom
        anchors.topMargin           : 10
        anchors.horizontalCenter    : topPanel.horizontalCenter
        color                       : Style.popup.backColor

        MonthModel {
            id: monthmodel
        }

        ListView
        {
            id          : hoursStats
            width       : parent.width
            height      : parent.height - headerRow.height - sumRow.height
            anchors.top : separator1.bottom
            model       : monthmodel
            delegate    : Rectangle {

                color   : Style.popup.backColor
                width   : hoursStats.width
                height  : hoursStats.height/5

                Row
                {
                    id      : modelRow
                    width   : parent.width
                    height  : parent.height

                    MText
                    {
                        mainText: model.date
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[0]
                    }
                    MText
                    {
                        mainText: model.clockIn
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[1]
                    }
                    MText
                    {
                        mainText: model.clockOut
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[2]
                    }
                    MText
                    {
                        mainText: model.total
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[3]
                    }
                    MText
                    {
                        mainText: model.difference
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[4]
                    }
                    MText
                    {
                        mainText: model.travel
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[5]
                    }
                    MText
                    {
                        mainText: model.holiday
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[6]
                    }
                    MText
                    {
                        mainText: model.sickday
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[7]
                    }
                    MText
                    {
                        mainText: model.vacation
                        textH   : parent.height
                        width   : bottomPanel.childrenWidth[8]
                    }
                }

                Rectangle  {
                    id          : separator2
                    width       : parent.width
                    height      : Style.popup.borderWidth/2
                    color       : Style.popup.borderColor

                    Component.onCompleted:{
                        if(!model.daychanged){
                            separator2.height = 0;
                        }
                    }
                }
            }
        }

        Row
        {
            id          : sumRow
            height      : parent.height/8
            anchors.top : headerRow.bottom

            MText{
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[0] + bottomPanel.childrenWidth[1] * 2
            }
            MText{
                id                  : totalSum
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]

                Component.onCompleted:
                {
                    mainText = monthmodel.getTotalSum()
                }
            }
            MText{
                id                  : differenceSum
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[4]

                Component.onCompleted:
                {
                    mainText = monthmodel.getDifferenceSum()
                }
            }
            MText{
                id                  : travelSum
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]

                Component.onCompleted:
                {
                    mainText = monthmodel.getTravelSum()
                }
            }
            MText{
                id                  : holidaySum
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]

                Component.onCompleted:
                {
                    mainText = monthmodel.getHolidaySum()
                }
            }
            MText{
                id                  : sickdaySum
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]

                Component.onCompleted:
                {
                    mainText = monthmodel.getSickdaySum()
                }
            }
            MText{
                id                  : vacationSum
                mainText            : ""
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]

                Component.onCompleted:
                {
                    mainText = monthmodel.getVacationSum()
                }
            }
        }

        Row
        {
            id          : headerRow
            height      : parent.height/8
            anchors.top : bottomPanel.top

            MText{
                id: day
                mainText            : "Dan"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[0]
                y                   : parent.height/2
            }
            MText{
                id: clockIn
                mainText            : "Dolazak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]
                y                   : parent.height/2
            }
            MText{
                id: clockOut
                mainText            : "Odlazak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[2]
                y                   : parent.height/2
            }
            MText{
                id: total
                mainText            : "Sat"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[3]
            }
            MText {
                id: difference
                mainText            : "Višak Manjak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[4]
            }
            MText  {
                id: travel
                mainText            : "Putni sat"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[5]
            }
            MText {
                id: holiday
                mainText            : "Praznik"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[6]
            }
            MText  {
                id: sickday
                mainText            : "Bolovanje"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[7]
            }
            MText
            {
                id: vacation
                mainText            : "Godišnji"
                textH               : parent.height
                width               : bottomPanel.childrenWidth[8]
            }
        }

        Rectangle  {
            id          : separator1
            width       : bottomPanel.width
            height      : Style.popup.borderWidth
            color       : Style.popup.borderColor
            anchors.top : sumRow.bottom
        }
    }
}
