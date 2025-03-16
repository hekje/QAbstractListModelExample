import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 50
    height: 50

    property var myObject

    // Debugging log to see when the delegate is created
    Component.onCompleted: {
        console.log("ObjectDisplay created with object:", myObject)
        if (myObject) {
            // Print x and y values
            console.log("ObjectDisplay - posX:", myObject.x, ", posY:", myObject.y)
        } else {
            console.log("ObjectDisplay - ERROR! Object is null")
        }
    }

    Rectangle {
        width: 50
        height: 50
        color: "red"

        Text {
            text: "!"
            color: "white"
            font.pixelSize: 24
            anchors.centerIn: parent
        }
    }
}
