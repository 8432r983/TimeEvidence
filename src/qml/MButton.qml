import QtQuick 2.12
import Style 1.0

MouseArea
{
    id: mbutton

    property int buttonW: 0 //MAR this could be int
    property int buttonH: 0 // MAR this could be int...

    property string buttonText: ""
    property int textSize: 0 //!!!is it pixel or what!!
    property int borderW: Style.popup.borderWidth

    width: buttonW
    height: buttonH

    Rectangle
    {
        anchors.centerIn: parent
        border.color: if(mbutton.containsPress)
                      {
                          return Style.popup.backColor
                      }
                      else return Style.popup.borderColor

        border.width: borderW

        color: if(mbutton.containsPress)
               {
                   return Style.popup.borderColor
               }
               else return Style.popup.backColor


        width: buttonW
        height: buttonH

        radius: Style.popup.borderRadius
    }

    Text
    {
        id: buttontext
        text: buttonText
        anchors.centerIn: parent
        font.pixelSize: mbutton.textSize
        anchors.margins: 10
        color: if(mbutton.containsPress)
               {
                   return Style.popup.backColor
               }
               else return Style.popup.borderColor
        // MAR dont mis back with border... keep stuff sperated..
    }
}
