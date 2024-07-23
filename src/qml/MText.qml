import QtQuick 2.9
import Style 1.0


Rectangle
{
    id: mtextRect

    property int textH        : 0
    property string mainText  : ""
    property bool boldEnable  : false
    property bool selected    : false

    height          : textH
    color           : Style.popup.backColor

    Rectangle
    {
        anchors.centerIn    : parent
        color               : mtextRect.selected ? Style.popup.borderColor : Style.popup.backColor
        width               : parent.width - Style.popup.borderWidth*2
        height              : parent.height - Style.popup.borderWidth*2 * !parent.eraseVerticalBorder
    }

    Text
    {
        id                  : mtext
        anchors.centerIn    : parent
        color               : mtextRect.selected ? Style.popup.backColor : Style.popup.borderColor
        font.pixelSize      : parent.textH * 0.56
        text                : parent.mainText
        font.bold           : boldEnable
        horizontalAlignment : Text.AlignHCenter
    }
}
