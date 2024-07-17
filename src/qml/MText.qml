import QtQuick 2.12
import Style 1.0


Rectangle
{
    property int textH        : 0
    property string mainText  : ""
    property bool boldEnable  : false

    height          : textH
    color           : Style.popup.backColor

    Rectangle
    {
        anchors.centerIn    : parent
        color               : Style.popup.backColor
        width               : parent.width - parent.border.width*2
        height              : parent.height - parent.border.width*2 * !parent.eraseVerticalBorder
    }

    Text
    {
        id                  : mtext
        anchors.centerIn    : parent
        color               : Style.popup.borderColor
        font.pixelSize      : parent.textH * 0.6
        text                : parent.mainText
        font.bold           : boldEnable
        horizontalAlignment : Text.AlignHCenter
    }
}
