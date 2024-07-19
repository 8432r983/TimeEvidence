import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

import Style 1.0

Popup
{
    property int axisZ: 0

    id  : vacationPopup
    z   : axisZ

    signal datesSignal(string dates)

    width   : Style.dispWidth
    height  : Style.dispHeight

    background  : Rectangle {
        color: Style.popup.backColor
    }

    function convert(date) {
        if(date === undefined){return ""}
        return date.getDate() + "." + (date.getMonth()+1).toString() + "." + date.getFullYear()
    }

    Rectangle
    {
        id                          : datePanel
        height                      : parent.height * 0.2
        width                       : parent.width
        anchors.top                 : parent.top
        anchors.horizontalCenter    : parent.horizontalCenter
        color                       : Style.popup.backColor

        MText
        {
            id          : startVacation
            width       : parent.width * 0.5
            anchors.left: parent.left
            mainText    : "Od: " + convert(datePicker.startDate)
            textH       : parent.height * 0.6
        }

        MText
        {
            id              : endVacation
            anchors.right   : parent.right
            width           : parent.width - startVacation.width
            mainText        : "Do: " + convert(datePicker.endDate)
            textH           : parent.height * 0.6
        }
    }

    Calendar
    {
        id                          : datePicker
        width                       : parent.width
        height                      : parent.height - buttonPanel.height - datePanel.height
        anchors.horizontalCenter    : parent.horizontalCenter
        anchors.top                 : datePanel.bottom
        locale                      : Qt.locale("hr_HR");

        property var startDate   : undefined
        property var endDate     : undefined

        property color todayColor: "red"

        function checkDate(dateA, dateB)
        {
            var res = dateA.getDate() === dateB.getDate() &&
                      dateA.getMonth() === dateB.getMonth() &&
                      dateA.getFullYear() === dateB.getFullYear()

            return res;
        }

        function calcColor(baseColor, highlightColor, styleData)
        {
            if(!styleData.visibleMonth)
            {
                return Style.popup.backColor
            }
            else if(styleData.visibleMonth){
                if(datePicker.startDate != undefined &&
                datePicker.checkDate(datePicker.startDate,styleData.date))
                {
                    return highlightColor
                }

                if(datePicker.endDate != undefined &&
                datePicker.checkDate(datePicker.endDate,styleData.date))
                {
                    return highlightColor
                }

                if(datePicker.startDate != undefined && datePicker.endDate != undefined)
                {
                    if(datePicker.startDate < styleData.date && styleData.date < datePicker.endDate)
                    {
                        return Qt.darker(highlightColor)
                    }
                }
            }
            return baseColor
        }

        style: CalendarStyle
        {
            gridVisible : false

            dayDelegate: Rectangle {

                color: datePicker.calcColor(Style.popup.backColor, Style.popup.borderColor, styleData)

                MouseArea
                {
                    anchors.fill    : parent
                    width           : parent.width
                    height          : parent.height

                    onClicked:
                    {
                        if(datePicker.startDate == undefined && datePicker.endDate == undefined){
                            datePicker.startDate = styleData.date
                        }
                        else if(datePicker.endDate == undefined){
                            datePicker.endDate = styleData.date
                        }
                        else
                        {
                            datePicker.startDate = undefined
                            datePicker.endDate = undefined
                        }

                        if(datePicker.startDate > datePicker.endDate)
                        {
                            var temp = datePicker.startDate
                            datePicker.startDate = datePicker.endDate
                            datePicker.endDate = temp
                        }
                    }
                }

                Text
                {
                    visible             : styleData.valid
                    anchors.centerIn    : parent
                    text                : styleData.date.getDate()
                    font.pixelSize      : parent.height * 0.6
                    color               :
                    {
                        if(datePicker.checkDate(styleData.date, new Date()))
                        {
                            return datePicker.todayColor
                        }
                        return datePicker.calcColor(Style.popup.borderColor, Style.popup.backColor, styleData)
                    }
                }
            }
        }

        visibleMonth: new Date().getMonth()
        visibleYear : new Date().getFullYear()

        minimumDate: new Date(new Date().getFullYear(), 0, 1);
        maximumDate: new Date(new Date().getFullYear()+1, 0, 1);
    }

    Rectangle{

        id              : buttonPanel
        height          : parent.height * 0.2
        width           : parent.width
        anchors.bottom  : parent.bottom
        color           : Style.popup.backColor

        MButton
        {
            id                          : escapeButton
            buttonW                     : parent.width * 0.5
            buttonH                     : parent.height
            buttonText                  : "\u2B8C"
            textSize                    : buttonH * 0.7
            anchors.left                : parent.left
            anchors.verticalCenter      : parent.verticalCenter

            onClicked:
            {
                datePicker.startDate = undefined
                datePicker.endDate = undefined
                vacationPopup.close()
            }
        }

        MButton
        {
            id                          : confirmButton
            buttonW                     : parent.width - escapeButton.width
            buttonH                     : parent.height
            buttonText                  : "\u2713"
            textSize                    : buttonH * 0.6
            anchors.right               : parent.right
            anchors.verticalCenter      : parent.verticalCenter
        }
    }
}
