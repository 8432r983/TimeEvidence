import QtQuick 2.9
import QtQuick.Controls 2.2

import Style 1.0

import MonthModel 1.0
import MonthLogger 1.0

Popup
{
    id                  : mainPopup

    height      : Style.dispHeight;
    width       : Style.dispWidth;
    modal       : true; focus : true; margins : 0; padding : 0;
    closePolicy : Popup.NoAutoClose
    x           : parent ? ((parent.width  - width) /2) : 0
    y           : parent ? ((parent.height - height)/2) : 0
    z           : 1;
    background  : Rectangle {
        anchors.fill : parent;
        color        : Style.popup.backColor;
        border.width : 0;
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

    MLoader {id:popupLoader}

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

                    onClicked:
                    {
                        popupLoader.source = "qrc:/qml/TravelHoursPopup.qml"
                        popupLoader.item.axisZ = mainPopup.z + 1
                        popupLoader.loaded()
                    }

                    Connections
                    {
                        target: popupLoader.item
                        function hoursSignal(hr)
                        {
                            console.log("Odrađenih putnih sati: " + hr)
                            monthlogger.addEntry(leftPanel.employeeName, datetime.currentDay.slice(0,3),
                                                 datetime.formatted.toString().split(" ")[1],
                                                 "-", "-", hr, "-", "-", "-");
                            monthmodel.loadEntries(datetime.formatted.toString().split(" ")[1], leftPanel.employeeName);
                            popupLoader.source = ""
                        }
                    }
                }
                MButton
                {
                    id                          : vacationButton
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("ZAHTJEV ZA GO")
                    textSize                    : buttonH*0.5

                    onClicked:
                    {
                        popupLoader.source = "qrc:/qml/VacationPopup.qml"
                        popupLoader.item.axisZ = mainPopup.z + 1
                        popupLoader.loaded()
                    }
                }
                MButton
                {
                    id                          : sickDayButton1
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("BOLOVANJE SA DOZ")
                    textSize                    : parent.height * 0.07
                }
                MButton
                {

                    id                          : sickDayButton2
                    buttonW                     : exitButton.buttonW
                    buttonH                     : exitButton.buttonH
                    buttonText                  : qsTr("BOLOVANJE BEZ DOZ")
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
                    mainText            : qsTr("Višak sati:<br><b>" + vacationData.leftoverhours)
                    textH               : parent.height * 0.18
                }
                MText
                {
                    id                  : vacationDays
                    width               : parent.width
                    height              : parent.height * 0.5
                    mainText            : qsTr("Godišnji<br>odmor:<br><b>" + vacationData.vacationdays + "</b><br>dana")
                    textH               : parent.height * 0.17
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
                        leftPanel.endTime = datetime.formatted.toString().split(" ")[0];
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
                mainText            : monthmodel.totalSum
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]
            }
            MText{
                id                  : differenceSum
                mainText            : monthmodel.differenceSum
                textH               : parent.height
                width               : bottomPanel.childrenWidth[4]
            }
            MText{
                id                  : travelSum
                mainText            : monthmodel.travelSum
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]
            }
            MText{
                id                  : holidaySum
                mainText            : monthmodel.holidaySum
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]
            }
            MText{
                id                  : sickdaySum
                mainText            : monthmodel.sickdaySum
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]
            }
            MText{
                id                  : vacationSum
                mainText            : monthmodel.vacationSum
                textH               : parent.height
                width               : bottomPanel.childrenWidth[1]
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
