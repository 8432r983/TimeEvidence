import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3
import com.example 1.0

import QtQuick.Controls.Styles 1.4

Window {
    id: window
    width: 800
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: clockBox
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: window.height * 0.2
        color: "#CED3DC"

        Text {
            id: clockText
            text: Qt.formatDateTime(new Date(), "hh:mm:ss") // Initial time
            font.pixelSize: window.height * 0.13 // Adjust font size based on window height
            horizontalAlignment: Text.AlignHCenter // Center align horizontally
            verticalAlignment: Text.AlignVCenter // Center align vertically
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                margins: 30
            } // Position at the top center of the parent window
        }
    }

    Rectangle {
        id: bigBox
        anchors.top: clockBox.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#CED3DC" }
            GradientStop { position: 1.0; color: "#5B616A" }
        }
        Rectangle {
            id: leftBox
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#5B616A" }
                GradientStop { position: 1.0; color: "#CED3DC" }
            }
            anchors {
                left: parent.left
                right: parent.horizontalCenter
                top: parent.top
                bottom: parent.bottom
                topMargin: 20
                bottomMargin: 20
                leftMargin: 70
                rightMargin: 70
            }
            border.color: "grey"
            border.width: 1
            radius: 30
            clip: true
            ListView {
                id: listView
                anchors.fill: parent
                model: NameListModel {}
                delegate: MouseArea {
                    width: listView.width
                    height: 40

                    Text {
                        id: nameText
                        text: model.name
                        wrapMode: Text.WrapAnywhere
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.leftMargin: 10
                        color: (listView.currentIndex === model.index) ? "red" : "white"
                    }

                    onClicked: {
                        clickAnimation.start()
                        console.log("click")
                        listView.currentIndex = model.index
                    }

                    // Scale animation
                    SequentialAnimation {
                        id: clickAnimation
                        running: false

                        // Scale up
                        PropertyAnimation {
                            target: nameText
                            property: "scale"
                            to: 1.1
                            duration: 100
                            easing.type: Easing.InOutQuad
                        }

                        // Scale down
                        PropertyAnimation {
                            target: nameText
                            property: "scale"
                            to: 1.0
                            duration: 100
                            easing.type: Easing.InOutQuad
                        }
                    }
                }
            }
        }

        Rectangle {
            id: rightBox
            border.width: 1
            radius: 30
            border.color: "grey"
            anchors {
                left: parent.horizontalCenter
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                topMargin: 20
                bottomMargin: 20
                leftMargin: 40
                rightMargin: 40
            }
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#5B616A" }
                GradientStop { position: 1.0; color: "#CED3DC" }
            }

                TextField {
                    id: inputField
                    anchors.top: keyboard.top
                    anchors.topMargin: parent.height * 0.1
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.1
                    width: keyboard.width / 3
                    font.pixelSize: inputField.height * 0.53
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    layer.enabled: true
                    // layer.effect: DropShadow {
                    //     transparentBorder: true
                    //     samples: 20
                    // }
                }

                NumericKeyboard {
                    id: keyboard
                    width: rightBox.width * 0.5
                    anchors.bottom: parent.bottom
                    height: parent * 0.7
                    onKeyPressed: {
                        inputField.text += value
                        handleKey.handleKeyPress(value)
                    }
                    onDeletePressed: {
                        inputField.text = inputField.text.length > 0 ? inputField.text.slice(0, -1) : ""
                        handleKey.handleDeletePress()
                    }
                    onEnterPressed: {
                        console.log("Entered: " + inputField.text)
                        handleKey.handleEnterPress()
                    }
                    onLetterPressed: {
                        inputField.text += letter
                        handleKey.handleLetterPress(letter)
                    }
                }
            }

    }

    // Update the clock every second
    Timer {
        interval: 1000 // Update every second
        running: true // Start the timer immediately
        repeat: true // Repeat indefinitely
        onTriggered: {
            // Update the clock text
            clockText.text = Qt.formatDateTime(new Date(), "hh:mm:ss")
        }
    }
}
