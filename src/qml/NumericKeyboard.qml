import QtQuick 2.9
import QtQuick.Controls 2.9

Item {
    id: numericKeyboard
    anchors.fill: parent

    property real buttonWidth: numericKeyboard.width * 0.1
    property real buttonHeight: numericKeyboard.height * 0.1

    property real textSize: buttonHeight * 0.53

    property color buttonDefaultColor: "#4E5BF2"
    property color buttonPressedColor: Qt.darker(buttonDefaultColor, 1.2)

    signal keyPressed(int value)
    signal deletePressed()
    signal enterPressed()
    signal letterPressed(string letter)

    Column {
        spacing: 10
        anchors.centerIn: parent

        Row {
            spacing: 10
            Repeater {
                model: 3
                delegate: Button {
                    width: numericKeyboard.buttonWidth
                    height: numericKeyboard.buttonHeight

                    text: (index + 1).toString()
                    font.pixelSize: numericKeyboard.textSize
                    background: Rectangle {
                        color: "lightgray"
                        radius: 5
                        layer.enabled: true
                        // layer.effect: DropShadow {
                        //     transparentBorder: true
                        //     samples: 20
                        // }
                    }
                    onClicked: numericKeyboard.keyPressed(index + 1)
                }
            }

            Button {
                width: numericKeyboard.buttonWidth
                height: numericKeyboard.buttonHeight
                text: "A"
                font.pixelSize: numericKeyboard.textSize
                background: Rectangle {
                    color: "lightblue"
                    radius: 5
                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }
                onClicked: numericKeyboard.letterPressed("A")
            }
        }

        Row {
            spacing: 10
            Repeater {
                model: 3
                delegate: Button {
                    width: numericKeyboard.buttonWidth
                    height: numericKeyboard.buttonHeight
                    text: (index + 4).toString()
                    font.pixelSize: numericKeyboard.textSize
                    background: Rectangle {
                        color: "lightgray"
                        radius: 5
                        layer.enabled: true
                        // layer.effect: DropShadow {
                        //     transparentBorder: true
                        //     samples: 20
                        // }
                    }
                    onClicked: numericKeyboard.keyPressed(index + 4)
                }
            }

            Button {
                width: numericKeyboard.buttonWidth
                height: numericKeyboard.buttonHeight
                text: "B"
                font.pixelSize: numericKeyboard.textSize
                background: Rectangle {
                    color: "lightblue"
                    radius: 5
                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }
                onClicked: numericKeyboard.letterPressed("B")
            }
        }

        Row {
            spacing: 10
            Repeater {
                model: 3
                delegate: Button {
                    width: numericKeyboard.buttonWidth
                    height: numericKeyboard.buttonHeight
                    text: (index + 7).toString()
                    font.pixelSize: numericKeyboard.textSize
                    background: Rectangle {
                        color: "lightgray"
                        radius: 5
                        layer.enabled: true
                        // layer.effect: DropShadow {
                        //     transparentBorder: true
                        //     samples: 20
                        // }
                    }
                    onClicked: numericKeyboard.keyPressed(index + 7)
                }
            }

            Button {
                width: numericKeyboard.buttonWidth
                height: numericKeyboard.buttonHeight
                text: "C"
                font.pixelSize: numericKeyboard.textSize
                background: Rectangle {
                    color: "lightblue"
                    radius: 5
                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }
                onClicked: numericKeyboard.letterPressed("C")
            }
        }

        Row {
            spacing: 10

            Button {
                width: numericKeyboard.buttonWidth
                height: numericKeyboard.buttonHeight
                text: "Del"
                font.pixelSize: numericKeyboard.textSize
                background: Rectangle {
                    color: "lightgray"
                    radius: 5
                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }
                onClicked: numericKeyboard.deletePressed()
            }

            Button {
                width: numericKeyboard.buttonWidth
                height: numericKeyboard.buttonHeight
                text: "0"
                font.pixelSize: numericKeyboard.textSize
                background: Rectangle {
                    color: "lightgray"
                    radius: 5
                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }
                onClicked: numericKeyboard.keyPressed(0)
            }

            Button {
                width: numericKeyboard.buttonWidth * 2.1
                height: numericKeyboard.buttonHeight
                text: "Enter"
                font.pixelSize: numericKeyboard.textSize
                background: Rectangle {
                    color: "lightgray"
                    radius: 5
                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }
                onClicked: numericKeyboard.enterPressed()
            }
        }
    }
}
