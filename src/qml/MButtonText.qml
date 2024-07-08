import QtQuick 2.9
import QtQml 2.9
import QtQuick.Controls 2.2

import Style 1.0

MouseArea  {

    QtObject {
        id : internal;
        property bool isDown     : false;

        property color bkgColor  : (isDown === true)
                                   ? Style.mButton.downColor
                                   : (isChecked === true)
                                     ? Style.mButton.downColor
                                     : Style.mButton.upColor;

        property color fontColor : (isDown === true)
                                   ? Style.mButton.fontDownColor
                                   :(isChecked === true)
                                     ? Style.mButton.fontDownColor
                                     : Style.mButton.fontUpColor;
        property bool fontIsBold : (isDown === true)
                                   ? true : (isChecked === true)
                                     ? true : false;
    }
    property int    angle       : 0;
    property int    fontSize    : Style.mButton.fontSize;
    property string fontFamily  : Style.general.fontFamily;
    property int    borderWidth : Style.mButton.borderWidth;
    property alias  text        : buttonText.text
    property bool   isChecked   : false;

    onPressed         : {internal.isDown = true; }
    onPressAndHold    : {internal.isDown = true; }
    onCanceled        : {internal.isDown = false;}
    onExited          : {internal.isDown = false;}
    onPositionChanged : {internal.isDown = false;}

    enabled                : true;
    implicitWidth          : Style.mButton.width;
    implicitHeight         : parent.height - 10;
    opacity                : (enabled)
                             ? Style.opacityMax
                             : Style.opacityMin;
    Rectangle {
        anchors.fill : parent;
        border.color : Style.mButton.borderColor;
        radius       : Style.mButton.borderRadius;
        border.width : borderWidth;
        color        : internal.bkgColor;
        Text {
            id                  : buttonText
            color               : internal.fontColor;
            font.family         : fontFamily;
            font.pixelSize      : fontSize;
            font.bold           : internal.fontIsBold;
            wrapMode            : Text.Normal;
            verticalAlignment   : Text.AlignVCenter;
            horizontalAlignment : Text.AlignHCenter;
            anchors.centerIn    : parent;
            rotation            : angle;
        }
    }
}
