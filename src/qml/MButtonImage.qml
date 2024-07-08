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
        property string imageUp   : "qrc:/images/downMenu/" + image + ".png";
        property string imageDown : "qrc:/images/downMenu/" + image + "Down.png";
    }

    property int    borderWidth : Style.mButton.borderWidth
    property string image       : "sysMute";
    property real   imageScale  : 0.7;
    property bool   isChecked   : false;
    property alias   mirror     : buttonImage.mirror;

    onPressed         : {internal.isDown = true; }
    onPressAndHold    : {internal.isDown = true; }
    onCanceled        : {internal.isDown = false;}
    onExited          : {internal.isDown = false;}
    onPositionChanged : {internal.isDown = false;}

    //enabled                : parent.enabled;
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
        Image {
            id               : buttonImage;
            height           : parent.height * imageScale;
            source           : (internal.isDown === true)
                               ? internal.imageDown : internal.imageUp;
            anchors.centerIn : parent;
            fillMode         : Image.PreserveAspectFit;
        }
    }
}
