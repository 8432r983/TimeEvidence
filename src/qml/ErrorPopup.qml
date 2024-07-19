import QtQuick 2.9
import QtQuick.Controls 2.2

import Style 1.0

Popup
{
    id: errorPopup
    width       : Style.dispWidth;
    height      : Style.dispHeight;
    modal       : true;
    focus       : true;
    margins     : 0;
    padding     : 0;
    closePolicy : Popup.NoAutoClose
    x           : parent ? ((parent.width - width)/2) :0
    y           : parent ? ((parent.height - height)/2) :0
    z:1;
    background  : Rectangle { anchors.fill: parent;color:
            Style.popup.backColor ;border.width: 0; opacity: Style.opacityMin; }

    property string message: ""

    Rectangle {
        width  : parent.width - Style.popup.margines;
        height : parent.height -Style.popup.margines;
        color  : Style.dispBgColor
        border {
            width : Style.popup.borderWidth;
            color : Style.popup.borderColor;
        }
        anchors.centerIn : parent;
        Text  {
            anchors.centerIn    : parent
            font.pixelSize      : parent.height * 0.1
            text                : message
            color               : Style.popup.borderColor
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked:
        {
            errorPopup.close();
        }
    }
}
