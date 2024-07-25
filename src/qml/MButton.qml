import QtQuick 2.9
import Style 1.0

MouseArea
{
    id: mbutton

    property int buttonW        : 0
    property int buttonH        : 0
    property string buttonText  : ""
    property int textSize       : 0
    property int borderW        : Style.popup.borderWidth
    property bool glowing       : false

    width  : buttonW
    height : buttonH

    Rectangle
    {
        anchors.centerIn: parent
        border.color: if(mbutton.containsPress)
                      {
                          return Style.popup.backColor
                      }
                      else return Style.popup.borderColor

        border.width: glowing ? borderW*4 : borderW
        color: if(mbutton.containsPress)
               {
                   return Style.popup.borderColor
               }
               else return Style.popup.backColor


        width   : buttonW
        height  : buttonH


        radius: Style.popup.borderRadius
    }

    Text
    {
        id                  : buttontext
        text                : buttonText
        anchors.centerIn    : parent
        font.pixelSize      : mbutton.textSize
        anchors.margins     : 10
        font.bold           : glowing
        color: if(mbutton.containsPress)
               {
                   return Style.popup.backColor
               }
               else return Style.popup.borderColor
    }
}
