import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Style 1.0

import HoursManager 1.0
import EmployeeModel 1.0

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

    HoursManager {id:hoursManager}

    function setData(data) {
        // Tisučputa sam rekao da vidim ostali variabli a nem vidm ih na ekran... :(
        leftPanel.employeeName = data.name;
        leftPanel.employeeStatus = data.status;
        hoursManager.setMainPath(leftPanel.employeeName);
        if(entries.getInOut(leftPanel.employeeName) === "") {
            entries.setInOut(leftPanel.employeeName, "D");
        }
        leftPanel.buttonsEnabled = entries.getInOut(leftPanel.employeeName) === "D";
        entriesModel.loadEntries(
                    datetime.formatted.toString().split(" ")[1],
                    leftPanel.employeeName);
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
            property string startTime       : ""
            property string endTime         : ""
            property bool buttonsEnabled    : entries.getInOut(leftPanel.employeeName) === "D"

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

            MButton
            {
                id                          : travelButton
                anchors.horizontalCenter    : exitButton.horizontalCenter
                anchors.bottom              : vacationButton.top
                anchors.bottomMargin        : 10
                buttonW                     : exitButton.buttonW
                buttonH                     : exitButton.buttonH
                buttonText                  : qsTr("SATI PUTA")
                textSize                    : buttonH*0.5
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
                buttonH                     : parent.height * 0.17
                buttonText                  : "\u2B8C"
                textSize                    : parent.height * 0.15

                onClicked : mainPopup.close();
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
                    enabled                     : leftPanel.buttonsEnabled
                    opacity                     : leftPanel.buttonsEnabled ? 1.0 : 0.3

                    onClicked:
                    {
                        leftPanel.startTime = datetime.formatted.toString().split(" ")[0];
                        entries.setStartTime(leftPanel.employeeName, leftPanel.startTime);
                        entries.setInOut(leftPanel.employeeName, "O");
                        leftPanel.buttonsEnabled = entries.getInOut(leftPanel.employeeName) === "D";
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
                    enabled                 : !leftPanel.buttonsEnabled
                    opacity                 : !leftPanel.buttonsEnabled ? 1.0 : 0.3

                    onClicked:
                    {
                        //leftPanel.endTime = datetime.formatted.toString().split(" ")[0];
                        leftPanel.endTime = leftPanel.intToTime(leftPanel.timeToInt(datetime.formatted.toString().split(" ")[0]) + Math.round(Math.random() * 100));

                        if(entries.getInOut(leftPanel.employeeName) === "O")
                        {
                            hoursManager.addEntry(datetime.currentDay.slice(0,3),
                                                  datetime.formatted.toString().split(" ")[1],
                                                  entries.getStartTime(leftPanel.employeeName),
                                                  leftPanel.endTime);
                            entries.setInOut(leftPanel.employeeName, "D");
                            //entries.setStartTime(leftPanel.employeeName, 0);
                        }

                        leftPanel.buttonsEnabled = entries.getInOut(leftPanel.employeeName) === "D";

                        entriesModel.loadEntries(datetime.formatted.toString().split(" ")[1], leftPanel.employeeName);
                    }
                }
            }
        }
    }

    Rectangle
    {
        property int childrenWidth: parent.width/6

        id                          : bottomPanel
        width                       : parent.width
        height                      : parent.height - topPanel.height
        anchors.top                 : topPanel.bottom
        anchors.topMargin           : 10
        anchors.horizontalCenter    : topPanel.horizontalCenter
        color                       : Style.popup.backColor

        EmployeeModel {id: entriesModel}

        ListView
        {
            id          : hoursStats
            width       : parent.width
            height      : parent.height - headerRow.height - summaryRow.height
            anchors.top : headerRow.bottom
            model       : entriesModel
            delegate    : Row
            {
                height  : hoursStats.height/5

                MText
                {
                    mainText: model.day
                    textH   : parent.height
                    width   : bottomPanel.childrenWidth
                }
                MText
                {
                    mainText: model.clockIn
                    textH   : parent.height
                    width   : bottomPanel.childrenWidth
                }
                MText
                {
                    mainText: model.clockOut
                    textH   : parent.height
                    width   : bottomPanel.childrenWidth
                }
                MText
                {
                    mainText: model.total
                    textH   : parent.height
                    width   : bottomPanel.childrenWidth
                }
                MText
                {
                    mainText: model.difference
                    textH   : parent.height
                    width   : bottomPanel.childrenWidth
                }
                MText
                {
                    mainText: model.travel
                    textH   : parent.height
                    width   : bottomPanel.childrenWidth
                }
            }
        }

        Row
        {
            id          : headerRow
            height      : parent.height/8
            anchors.top : summaryRow.bottom

            MText
            {
                mainText            : "Dan"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false
            }
            MText
            {
                mainText            : "Dolazak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                mainText            : "Odlazak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                mainText            : "Sat"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                mainText            : "Višak Manjak"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
            MText
            {
                mainText            : "Putni sat"
                textH               : parent.height
                width               : bottomPanel.childrenWidth
                eraseVerticalBorder : false

            }
        }

        Row
        {
            id              : summaryRow
            height          : parent.height/8
            anchors.top     : bottomPanel.top

            property int summaryWidth: parent.width/4

            MText
            {
                mainText            : "Odrađeno"
                textH               : parent.height
                width               : summaryRow.summaryWidth
                eraseVerticalBorder : false

            }
        }
    }
}
