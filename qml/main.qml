import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 800
    title: "Controller-QML Example"

    signal buttonPressed
    // Define a signal

    // Text element to display the message
    Text {
        id: messageText
        text: controller ? controller.message : "No message available" // Check if controller is not null - Bind the text to the C++ message property
        anchors.centerIn: parent
        anchors.top: parent.top // Align the text to the bottom of the screen
        anchors.topMargin: 50 // Set some margin from the top
        font.pointSize: 20
        color: "blue"
    }

    // Button moved up
    Button {
        text: "Add Object"
        anchors.top: parent.top // Place the button at the top of the screen
        anchors.horizontalCenter: parent.horizontalCenter // Center horizontally
        anchors.topMargin: 20 // Add some margin from the top
        onClicked: buttonPressed() // Emit the custom signal
    }

    Repeater {
        model: controller ? controller.objModel : [] // Ensure the model is a list, even if the controller is null
        delegate: ObjectDisplay {
            myObject: object
            x: object ? object.x : 0
            y: object ? object.y : 0

            Component.onCompleted: {
                console.log("Object type:", typeof object)
                console.log("Object properties:",
                            JSON.stringify(Object.keys(object)))

                // Try to access m_x and m_y and log the results
                console.log("main.qml - object.m_x:", object.x, ", object.m_y:", object.y)
            }
        }
    }
}
