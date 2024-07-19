pragma Singleton
import QtQuick 2.9
import QtQml 2.2
import QtQuick.Window 2.2

QtObject {
    readonly property int    dispWidth               :  1366;
    readonly property int    dispHeight              :  768;
    readonly property color  dispBgColor             : "black";

    readonly property real opacityMin :0.5;

    // added for ITAMS-DISP
    readonly property QtObject popup               : QtObject {
        readonly property int    margines          : 150
        readonly property color  backColor         : "black"
        readonly property color  borderColor       : "white"
        readonly property int    borderWidth       : 2
        readonly property int    borderRadius      : 10
    }

}

