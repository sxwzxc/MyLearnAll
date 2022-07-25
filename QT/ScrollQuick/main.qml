import QtQuick 2.12
import QtQuick.Controls 2.5
import QtMultimedia 5.0


//ApplicationWindow {
//    width: 640
//    height: 480
//    visible: true
//    title: qsTr("Scroll")
/*
    Rectangle {
         id: page
         width: 500; height: 500
         color: "lightgray"
         ListView {
             id: listView
             width: parent.width
             model: 20
             delegate: ItemDelegate {
                 text: "Item " + (index + 1)
                 width: listView.width
             }
         }
         Text {
             id: helloText
             text: "Hello world!"
             y: 50
             anchors.horizontalCenter: page.horizontalCenter
             font.pointSize: 24; font.bold: true
         }
     }
*/
//    ScrollView {
//        anchors.fill: parent
//
//        ListView {
//            id: listView
//            width: parent.width
//            model: 20
//            delegate: ItemDelegate {
//                text: "Item " + (index + 1)
//                width: listView.width
//            }
//        }
//    }
//}

import QtQuick.Window 2.2

Rectangle {
    visible: true
    width: 960
    height: 720

    ListView {
        id : listView

        width: parent.width * 0.5
        height: parent.height
        anchors.margins: 20
        clip: true
        model: 100
        delegate: numberDelegate
        spacing: 5
        focus: true
        currentIndex: -1

        property var lastCurrentIndex: -1
    }

    Component {
        id: numberDelegate
        Rectangle {
            width: ListView.view.width
            height: 40

            border.color: Qt.lighter(color, 1.1)
            color: listView.currentIndex == index ? "red" :"green"

            Text {
                anchors.centerIn: parent
                font.pixelSize: 10
                text: index
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true

                onPressed: {
                    if (listView.lastCurrentIndex != -1) {
                        if(listView.itemAtIndex(listView.lastCurrentIndex)){
                            listView.itemAtIndex(listView.lastCurrentIndex).color = "green"
                        }
                    }

                    listView.currentIndex = index
                    color = "red"

                    listView.lastCurrentIndex = index
                  }

                onEntered: {

                    if (listView.currentIndex == index) {
                        return
                    }
                    color = "blue"
                }
                onExited: {

                     if (listView.currentIndex == index) return
                     color = "green"
                }

            }
        }
    }

}
