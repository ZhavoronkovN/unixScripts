import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Task1_logic 1.0

Item {
    id:main
    Rectangle{
        id:rect_dir
        width: parent.width
        height:60
        anchors.margins: 5
        anchors.top: parent.top
        TextField{
            id:text_dir
            width: parent.width-220
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            anchors.leftMargin: 20
            font.pixelSize: 20
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            background: Rectangle{
                color: "whitesmoke"
            }
            focus: true
        }
        Button{
            id: button_dir
            text: "Select directory"
            anchors.margins: 10
            anchors.rightMargin: 20
            anchors.right: parent.right
            anchors.left : text_dir.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            font.pixelSize: 20
            onClicked: file_dial.open();
        }
    }
    Rectangle{
        id: rect_type
        width: (parent.width-40)/2
        height: 50
        anchors.margins: 5
        anchors.left: parent.left
        anchors.top: rect_dir.bottom
        TextField{
            id: text_type
            anchors{
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                leftMargin: 15
            }
            text: "test"
            font.pixelSize: 20
        }
    }
    Rectangle{
        id: rect_tools
        width: 320
        height: 90
        anchors.margins: 5
        anchors.right: parent.right
        anchors.top: rect_dir.bottom
        anchors.rightMargin : 20+(parent.width/2-340)/2
        Label{
            id: lab_tools
            anchors{
                topMargin: 10
                right: row_tools.left
                top: parent.top
                bottom: parent.bottom
            }
            text: "Ask before deleting "
            font.pixelSize: 20
        }
            Row{
                id: row_tools
                anchors{
                    right: parent.right
                    top: parent.top
                    topMargin: 5
                    bottom: parent.bottom
                }
                RadioButton{
                    text: "Yes"
                    onClicked: logic.SafeModeOn=true;
                }
                RadioButton{
                    text: "No"
                    checked: true
                    onClicked: logic.SafeModeOn=false;
                }
        }
    }
    TextArea{
        id:res_text
        anchors{
            top: rect_tools.bottom
            bottom: rect_but.top
            left: parent.left
            right: parent.right
            leftMargin: 20
            rightMargin: 20
            bottomMargin: 10
        }
        font.pixelSize: 20
        background: Rectangle{
            color: "whitesmoke"
        }
    }
    Rectangle{
        id:rect_but
        anchors{
            bottom: parent.bottom
        }
        height: 100
        width: parent.width
        Button{
            id:but_help
            anchors{
                left: parent.left
                leftMargin: 20
            }
            font.pixelSize: 20
            width: 80
            text: "Help"
            onClicked: help_dial.open();
        }
        Button{
            id:but_start
            anchors{
                right: parent.right
                rightMargin: 20
            }
            font.pixelSize: 20
            width: 120
            text: "Start"
            onClicked: logic.slotStartRemoving(text_dir.text,text_type.text);
        }
    }
    FileDialog{
        id: file_dial
        selectFolder: true
        onAccepted: text_dir.text+=fileUrl.toString().slice(8);
    }
    MessageDialog{
        id: help_dial
        title: "Help"
        text: "\t1) Select folder by typing it or selecting in dialog.\n
               \t2) Specify file type.\n
               \t3) The program will delete in the folder and its subfolders files of the file type."
    }
    MessageDialog{
        id: remove_dial
        title: "Remove?"
        property string file: ""
        text: "Remove "+file+" ?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: logic.slotRemoveAccepted();
        onNo:  logic.slotRemoveRejected();
    }
    Task1_logic{
        id: logic
        onWriteMessage:{
            res_text.text+=message;
        }
        onAskForRemove: {
            remove_dial.file=file;
            remove_dial.open();
        }
    }
}
