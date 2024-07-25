import QtQuick 2.9
import Style 1.0


Rectangle
{
    id: mtextRect

    property int textH        : 0
    property string mainText  : ""
    property bool boldEnable  : false
    property color textColor  : Style.popup.borderColor

    height          : textH
    color           : Style.popup.backColor

    Text
    {
        id                  : mtext
        anchors.centerIn    : parent
        color               : parent.textColor
        font.pixelSize      : parent.textH * 0.56
        text                : parent.mainText
        font.bold           : boldEnable
        horizontalAlignment : Text.AlignHCenter
    }
}
