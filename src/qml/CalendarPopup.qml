import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

import Style 1.0

Popup
{
    id: calendarPopup

    property string popupTitle  : "Title"
    property string employeeName: ""

    property date lowerBound: new Date()
    property date upperBound: new Date()

    property bool isVacationPopup: false

    signal dateSignal(var dates);

    width   : Style.dispWidth
    height  : Style.dispHeight

    background  : Rectangle {
        color: Style.popup.backColor
    }

    function convert(date) {
        if(date === undefined){return "-"}
        return date.getDate() + "." + (date.getMonth()+1).toString() + "." + date.getFullYear()
    }

    Rectangle
    {
        id                          : titleBox
        height                      : parent.height * 0.1
        width                       : parent.width
        anchors.horizontalCenter    : parent.horizontalCenter
        color                       : Style.popup.backColor

        MText
        {
            width                   : parent.width * 0.5
            anchors.verticalCenter  : parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            mainText                : calendarPopup.popupTitle
            height                  : parent.height - Style.popup.borderWidth*2
            textH                   : parent.height
        }
    }

    Rectangle
    {
        id                          : datePanel
        height                      : parent.height * 0.1
        width                       : parent.width
        anchors.horizontalCenter    : parent.horizontalCenter
        anchors.top                 : titleBox.bottom
        color                       : Style.popup.backColor

        MText
        {
            id                      : startVacation
            width                   : parent.width * 0.5
            anchors.verticalCenter  : parent.verticalCenter
            anchors.left            : parent.left
            mainText                : "Od: " + calendarPopup.convert(datePicker.startDate)
            textH                   : parent.height
        }

        MText
        {
            id                      : endVacation
            width                   : parent.width - startVacation.width
            anchors.verticalCenter  : parent.verticalCenter
            anchors.right           : parent.right
            mainText                : "Do: " + calendarPopup.convert(datePicker.endDate)
            textH                   : parent.height
        }
    }

    MText{
        id          : difference
        width       : parent.width
        height      : parent.height * 0.1
        anchors.top : datePanel.bottom
        textH       : height * 0.6

        mainText: {
            if(datePicker.startDate === undefined || datePicker.endDate === undefined){
                return calendarPopup.popupTitle + " dani: -"
            }
            return calendarPopup.popupTitle + " dani: " + dateranges.dateDist(datePicker.startDate, datePicker.endDate);
        }
    }

    Calendar
    {
        id                          : datePicker
        width                       : parent.width
        height                      : parent.height - buttonPanel.height - datePanel.height - titleBox.height - difference.height
        anchors.horizontalCenter    : parent.horizontalCenter
        anchors.top                 : difference.bottom
        //locale                      : Qt.locale("hr_HR");

        property var startDate   : undefined
        property var endDate     : undefined

        property color todayColor   : "red"
        property color holidayColor : "blue"

        property var monthMap: {"January":"Siječanj",
            "February":"Veljača",
            "March":"Ožujak",
           "April":"Travanj",
            "May":"Svibanj",
            "June":"Lipanj",
            "July":"Srpanj",
            "August":"Kolovoz",
            "September":"Rujan",
            "October":"Listopad",
            "November":"Studenti",
            "December":"Prosinac"}

        function checkDate(dateA, dateB)
        {
            var res = dateA.getDate() === dateB.getDate() &&
                      dateA.getMonth() === dateB.getMonth() &&
                      dateA.getFullYear() === dateB.getFullYear()

            return res;
        }

        function calcColor(baseColor, highlightColor, styleData)
        {
            if(styleData.date < datePicker.minimumDate || styleData.date > datePicker.maximumDate)
            {
                return Style.popup.backColor
            }
            else if((styleData.date > datePicker.minimumDate && styleData.date < datePicker.maximumDate)){
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

            navigationBar: Rectangle{
                height : datePicker.height * 0.15
                color  : Style.popup.backColor

                MButton
                {
                    id                      : previousMonthButton
                    anchors.left            : parent.left
                    anchors.leftMargin      : 10
                    anchors.verticalCenter  : parent.verticalCenter
                    buttonH                 : parent.height - Style.popup.borderWidth * 4
                    buttonW                 : buttonH + Style.popup.borderWidth
                    buttonText              : "\u2B9C"
                    textSize                : buttonH * 0.6
                    onClicked               : control.showPreviousMonth()
                }

                MText
                {
                    anchors.horizontalCenter    : parent.horizontalCenter
                    anchors.verticalCenter      : parent.verticalCenter
                    mainText                    : datePicker.monthMap[styleData.title.split(" ")[0]] + " " + styleData.title.split(" ")[1]
                    textH                       : parent.height
                }

                MButton
                {
                    id                      : nextMonthButton
                    anchors.right           : parent.right
                    anchors.rightMargin     : 10
                    anchors.verticalCenter  : parent.verticalCenter
                    buttonH                 : parent.height - Style.popup.borderWidth * 4
                    buttonW                 : buttonH + Style.popup.borderWidth
                    buttonText              : "\u2B9E"
                    textSize                : buttonH * 0.6
                    onClicked               : control.showNextMonth()
                }
            }

            dayOfWeekDelegate: Rectangle
            {
                height : datePicker.height * 0.15

                MText
                {
                    anchors.fill        : parent
                    anchors.centerIn    : parent
                    mainText            : ["ned","pon","uto","sri","čet","pet","sub"][styleData.dayOfWeek]
                    //mainText            :control.locale.dayName(styleData.dayOfWeek, control.dayOfWeekFormat)
                    textH               : parent.height * 0.8
                }
            }

            dayDelegate: Rectangle {
                color: datePicker.calcColor(Style.popup.backColor, Style.popup.borderColor, styleData)

                MouseArea
                {
                    anchors.fill    : parent
                    width           : parent.width
                    height          : parent.height

                    onClicked:
                    {
                        if(styleData.date < datePicker.minimumDate || styleData.date > datePicker.maximumDate)
                        {
                            return;
                        }

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
                        if(holidaycheck.holidayCheck(styleData.date))
                        {
                            return datePicker.holidayColor
                        }
                        else if(datePicker.checkDate(styleData.date, new Date()))
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

        minimumDate: calendarPopup.lowerBound
        maximumDate: calendarPopup.upperBound
    }

    MLoader { id: listLoader }

    MButton {
        id                          : refreshButton
        anchors.left                : parent.left
        anchors.top                 : parent.top
        buttonW                     : parent.width / 10
        buttonH                     : parent.height / 10
        buttonText                  : "\u27F3"
        textSize                    : buttonH
        anchors.topMargin           : 15
        anchors.leftMargin          : 15
        onClicked                   :
        {
            datePicker.visibleMonth = new Date().getMonth()
            datePicker.visibleYear = new Date().getFullYear()
        }
    }

    MButton {
        id                          : listVacationButton
        enabled                     : calendarPopup.isVacationPopup
        visible                     : calendarPopup.isVacationPopup
        anchors.top                 : refreshButton.bottom
        anchors.horizontalCenter    : refreshButton.horizontalCenter
        buttonW                     : refreshButton.buttonW
        buttonH                     : refreshButton.buttonH
        buttonText                  : "\u2338"
        textSize                    : buttonH
        anchors.topMargin           : 15
        anchors.leftMargin          : 15
        onClicked                   :
        {
            listLoader.source = "qrc:/qml/VacationListPopup.qml";
            listLoader.item.z = calendarPopup.z + 1
            listLoader.item.employeeName = calendarPopup.employeeName
            vacationmodel.loadVacation(calendarPopup.employeeName)
            listLoader.loaded()
        }
    }

    Rectangle{

        id                  : buttonPanel
        height              : parent.height * 0.1
        width               : parent.width
        anchors.top         : datePicker.bottom
        anchors.topMargin   : 8
        color               : Style.popup.backColor

        MButton
        {
            id                          : escapeButton
            buttonW                     : parent.width * 0.5 - Style.popup.borderWidth*8
            buttonH                     : parent.height - Style.popup.borderWidth*4
            buttonText                  : "\u2B8C"
            textSize                    : buttonH * 0.7
            anchors.left                : parent.left
            anchors.leftMargin          : Style.popup.borderWidth*2
            anchors.verticalCenter      : parent.verticalCenter

            onClicked:
            {
                datePicker.startDate = undefined;
                datePicker.endDate = undefined;
                calendarPopup.close()
            }
        }

        MButton
        {
            id                          : confirmButton
            buttonW                     : parent.width - escapeButton.width - Style.popup.borderWidth*8
            buttonH                     : parent.height - Style.popup.borderWidth*4
            buttonText                  : "\u2713"
            textSize                    : buttonH * 0.6
            anchors.right               : parent.right
            anchors.rightMargin         : Style.popup.borderWidth*2
            anchors.verticalCenter      : parent.verticalCenter

            onClicked:
            {
                if(datePicker.startDate !== undefined && datePicker.endDate !== undefined){
                    calendarPopup.dateSignal({startDate: datePicker.startDate, endDate: datePicker.endDate});
                    datePicker.startDate = undefined;
                    datePicker.endDate = undefined;
                    calendarPopup.close();
                }
            }
        }
    }
}
