import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Style 1.0

Rectangle
{
    property real clockWidth    : 0
    property real clockHeight   : 0

    id              : clockPanel
    height          : clockHeight
    width           : clockWidth
    color           : Style.popup.backColor
    border.color    : Style.popup.borderColor

    Rectangle
    {
        anchors.horizontalCenter    : parent.horizontalCenter
        anchors.top                 : datePanel.bottom
        width                       : clockPanel.clockWidth
        height                      : clockPanel.clockHeight - datePanel.height
        color                       : Style.popup.backColor

        Text
        {
            id                  : clockText
            anchors.centerIn    : parent
            text                : datetime.formatted.toString().split(" ")[0]
            font.pixelSize      : parent.height * 0.6
            color               : Style.popup.borderColor
        }

        MText
        {
            id                      : holidayText
            anchors.right           : parent.right
            anchors.rightMargin     : parent.width * 0.15
            anchors.verticalCenter  : parent.verticalCenter
            textH                   : parent.height * 0.6
            mainText                : holidaycheck.holiday()
        }
    }

    Rectangle
    {
        id                          : datePanel
        anchors.horizontalCenter    : parent.horizontalCenter
        width                       : clockPanel.clockWidth
        height                      : clockPanel.clockHeight * 0.4
        color                       : Style.popup.backColor

        Text
        {
            id              : dateText
            x               : parent.width/2 - paintedWidth/2
            y               : parent.height/2
            width           : parent.width
            height          : parent.height
            font.pixelSize  : height*0.5
            text            : datetime.currentDay.toString() + " " + datetime.formatted.toString().split(" ")[1]
            color           : Style.popup.borderColor
        }
    }
}
