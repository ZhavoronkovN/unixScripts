import QtQuick 2.12
import QtQuick.Controls 2.12

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
            onClicked: console.log(main.height)
        }
    }
    Rectangle{
        id: rect_type
        width: (parent.width-40)/2
        height: 50
        anchors.margins: 5
        anchors.left: parent.left
        anchors.top: rect_dir.bottom
        ComboBox{
            id: combo_type
            anchors{
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                leftMargin: 15
            }
            currentIndex: 1
            displayText: "File type : " + currentText
            model : ["cpp","c","app","custom"]
            onDisplayTextChanged : {
             if(currentText==="custom"){
                 editable=true;
                 displayText="";
             }
             else{
                 editable=false;
             }
            }
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
                    checked: true
                }
                RadioButton{
                    text: "No"
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
        }
    }
}
