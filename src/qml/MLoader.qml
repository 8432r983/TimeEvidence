import QtQuick 2.12

import Style 1.0

Loader {
    id       : popupLoader
    width    : Style.dispWidth;
    height   : Style.dispHeight;
    source   : "";
    onLoaded : item.open();
}
