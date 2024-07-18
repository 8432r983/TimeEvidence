import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Style 1.0

Popup
{
    id: travelHoursPopup

    property string hours: ""

    signal hoursSignal(string hr)

    width   : Style.dispWidth
    height  : Style.dispHeight

    MLoader {id: popupLoader}

    background  : Rectangle {
        color           : Style.popup.backColor
    }

    MText
    {
        id                        : hoursText
        width                     : keyboard.width * 0.9
        textH                     : parent.height * 0.2
        border.color              : Style.popup.backColor
        border.width              : Style.popup.borderWidth
        anchors.bottom            : keyboard.top
        anchors.bottomMargin      : textH * 0.1
        anchors.horizontalCenter  : keyboard.horizontalCenter
    }

    NumericKeyboard
    {
        id: keyboard

        width               : parent.width
        height              : parent.height * 0.55 //- hoursText.height - escapeButton.height - Style.popup.borderWidth*4
        anchors.bottom      : parent.bottom
        anchors.bottomMargin: 20
        buttonWidth         : keyboard.width * 0.225
        buttonHeight        : keyboard.height * 0.19

        onKeyPressed: {
            hoursText.mainText += value.toString()
            travelHoursPopup.hours += value.toString();
        }
        onDeletePressed: {
            hoursText.mainText = hoursText.mainText.length > 0 ? hoursText.mainText.slice(0, -1) : "";
            travelHoursPopup.hours = travelHoursPopup.hours.length > 0 ? travelHoursPopup.hours.slice(0,-1) : "";
        }
        onEnterPressed: {
            travelHoursPopup.hours += ":00"
            travelHoursPopup.hoursSignal(travelHoursPopup.hours);
            travelHoursPopup.hours = ""
            hoursText.mainText = ""
            travelHoursPopup.close();
        }
    }

    MButton
    {
        id                          : escapeButton
        buttonW                     : keyboard.width * 0.9
        buttonH                     : parent.height * 0.2
        buttonText                  : "\u2B8C"
        textSize                    : buttonH * 0.7
        anchors.bottom              : hoursText.top
        anchors.horizontalCenter    : parent.horizontalCenter

        onClicked:
        {
            travelHoursPopup.hours = "";
            travelHoursPopup.close();
        }
    }
}
