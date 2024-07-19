import QtQuick 2.9
import QtQuick.Controls 2.2
import Style 1.0

Item {
    id: numericKeyboard

    property real buttonWidth: 0
    property real buttonHeight: 0

    property real textSize: buttonHeight * 0.8

    property bool lettersVisible: true

    signal keyPressed(int value)
    signal deletePressed()
    signal enterPressed()
    signal letterPressed(string letter)

    Column {
        spacing: 10
        anchors.centerIn: parent

        Row
        {
            spacing: 10
            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: letterPressed("C")

                buttonText: "C"
            }
            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: letterPressed("D")

                buttonText: "D"
            }
            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: letterPressed("E")

                buttonText: "E"
            }
            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: letterPressed("F")

                buttonText: "F"
            }
        }

        Row
        {
            spacing: 10
            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: keyPressed(8)

                buttonText: "8"
            }

            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: keyPressed(9)

                buttonText: "9"
            }

            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: letterPressed("A")

                buttonText: "A"
            }

            MButton
            {
                buttonW: buttonWidth
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: letterPressed("B")

                buttonText: "B"
            }
        }

        Row {
            spacing: 10
            Repeater {
                model: 4
                delegate: MButton
                {
                    buttonW: buttonWidth
                    buttonH: buttonHeight

                    textSize: numericKeyboard.textSize

                    onClicked: keyPressed(index+4)

                    buttonText: (index+4).toString()
                }
            }
        }

        Row {
            spacing: 10
            Repeater {
                model: 4
                delegate: MButton
                {
                    buttonW: buttonWidth
                    buttonH: buttonHeight
                    textSize: numericKeyboard.textSize

                    onClicked: keyPressed(index)

                    buttonText: index.toString()
                }
            }
        }

        Row {
            spacing: 10

            MButton
            {
                buttonW: buttonWidth * 2 + parent.spacing
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: deletePressed()

                buttonText: "\u232B"
            }

            MButton
            {
                buttonW: buttonWidth * 2 + parent.spacing
                buttonH: buttonHeight
                textSize: numericKeyboard.textSize

                onClicked: enterPressed()

                buttonText: "\u2713"
            }
        }
    }
}
