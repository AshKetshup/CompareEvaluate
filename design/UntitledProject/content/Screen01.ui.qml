/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import UntitledProject

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Image {
        id: image
        width: rectangle.width / 2 - 80
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 50
        anchors.topMargin: 70
        anchors.bottomMargin: 70
        source: "qrc:/qtquickplugin/images/template_image.png"
        scale: 1
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: image1
        x: 988
        width: rectangle.width / 2 - 80
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 50
        anchors.topMargin: 70
        anchors.bottomMargin: 70
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/qtquickplugin/images/template_image.png"
        scale: 1
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
