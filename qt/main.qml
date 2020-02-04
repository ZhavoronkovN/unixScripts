import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: main
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    minimumWidth: 640
    title: qsTr("Unix part 3") 
    TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Task 1")
        }
        TabButton {
            text: qsTr("Task 2")
        }
        TabButton {
            text: qsTr("Task 3")
        }
    }

    StackLayout {
        width: parent.width
        y:bar.height
        height: parent.height
        currentIndex: bar.currentIndex
        Task1 {
            id: task1
        }
        Task2 {
            id: task2
        }
        Task3 {
            id: task3
        }
    }
}
