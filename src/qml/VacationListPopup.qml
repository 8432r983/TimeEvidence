import QtQuick 2.9
import QtQuick.Controls 2.2

import Style 1.0

import VacationListModel 1.0

Popup {

    id      : vacationPopup
    width   : Style.dispWidth * 0.5
    height  : Style.dispHeight

    property string employeeName: ""

    VacationListModel
    {
        id: vacationmodel
    }

    background: Item {
        width: parent.width
        height: parent.height

        Rectangle{
            anchors.fill    : parent
            color           : Style.popup.backColor
            width           : parent.width
            height          : parent.height
        }
    }

    MButton{
        id                          : refreshButton
        buttonW                     : parent.width
        buttonH                     : parent.height / 11
        buttonText                  : "\u27F3"
        textSize                    : buttonH * 0.9
        onClicked                   : vacationmodel.loadVacation(vacationPopup.employeeName);
    }

    Row
    {
        property int textSize: parent.height/15

        id          : labelRow
        anchors.top : refreshButton.bottom
        width       : parent.width
        height      : refreshButton.height

        MText{
            mainText: "Datum"
            textH   : parent.textSize
            width   : parent.width * 0.3
        }
        MText{
            mainText: "Odobreno"
            textH   : parent.textSize
            width   : parent.width * 0.3
        }
        MText{
            mainText: "Datum zahtjeva"
            textH   : parent.textSize
            width   : parent.width * 0.4
        }
    }

    ListView
    {
        id          : vacationView
        anchors.top : labelRow.bottom
        width       : parent.width
        height      : parent.height - refreshButton.height - escapeButton.height - labelRow.height
        model       : vacationmodel

        delegate: Row {
            width       : vacationView.width
            height      : vacationView.height / 8

            MText{
                mainText: date
                textH   : labelRow.textSize
                width   : parent.width * 0.3
            }
            MText{
                mainText    : valid
                textH       : labelRow.textSize
                textColor   : mainText == "Da" ? "green" : "red"
                width       : parent.width * 0.3
            }
            MText{
                mainText: request
                textH   : labelRow.textSize
                width   : parent.width * 0.4
            }
        }
    }

    MButton{
        id                          : escapeButton
        buttonW                     : parent.width
        buttonH                     : parent.height / 11
        y                           : parent.height - buttonH - Style.popup.borderWidth * 2
        buttonText                  : "\u2B8C"
        textSize                    : buttonH * 0.7
        onClicked                   : vacationPopup.close()
    }
}
