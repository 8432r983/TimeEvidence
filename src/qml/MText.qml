import QtQuick 2.12
import Style 1.0

Text
{
    property int textH          : 0
    property string mainText    : ""

    color: Style.popup.borderColor
    font.pixelSize: textH * 0.6

    text: mainText
}
