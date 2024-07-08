import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Style 1.0

Popup
{
    id: errorPopup
    anchors.centerIn    : parent
    width               : parent.width * 0.7
    height              : parent.height * 0.7
    background          : Rectangle
                        {
                            color: Style.popup.backColor
                            border.width: Style.popup.borderWidth
                            border.color: Style.popup.borderColor
                        }

    property string message: ""
    opacity: 0.7

    Text
    {
        anchors.centerIn    : parent
        font.pixelSize      : parent.height * 0.1
        text                : message
        color               : Style.popup.borderColor
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            errorPopup.close();
        }
    }
}
