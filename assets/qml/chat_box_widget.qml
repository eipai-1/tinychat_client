import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: msgListView
    model: messageModel

    delegate: ItemDelegate {
        id: delegateRoot

        /* ???
         * width: parent.width 是错误的
         */
        width: ListView.view.width
        required property string msgText
        required property bool isMe
        contentItem: Row {
            id: itemRootRow
            spacing: 3
            layoutDirection: delegateRoot.isMe ? Qt.RightToLeft : Qt.LeftToRight

            Image {
                id: avatar
                anchors.verticalCenter: parent.verticalCenter
                width: 40
                height: 40
                source: "qrc:/images/users/avatar/default_avatar.png"
            }

            Rectangle {
                id: msgRect
                width: Math.min(parent.width / 2, msgEdit.implicitWidth + (msgEdit.x + msgBubble.x) * 2)
                height: msgBubble.height + msgBubble.x * 2
                property double msgMargin: 10
                property bool isLoaded: false

                property double bubbleMargin: 10
                property double triangleSize: 10
                property color otherBubbleColor: "#dff5d5"
                property color myBubbleColor: "#cce7f0"
                Rectangle {
                    id: bubbleTriangle
                    anchors.verticalCenter: parent.verticalCenter
                    x: delegateRoot.isMe ? msgBubble.x - width / 2 - width / 5 + msgBubble.width
                                         : msgBubble.x - width / 2 + width / 5
                    width: msgRect.triangleSize
                    height: msgRect.triangleSize
                    color: delegateRoot.isMe ? msgRect.myBubbleColor : msgRect.otherBubbleColor
                    rotation: 45
                    radius: width / 5
                }


                Rectangle {
                    id: msgBubble
                    width: parent.width - 2 * msgRect.bubbleMargin
                    height: msgEdit.height + msgEdit.x * 2
                    x: msgRect.bubbleMargin
                    y: msgRect.bubbleMargin
                    radius: x

                    color: delegateRoot.isMe ? msgRect.myBubbleColor : msgRect.otherBubbleColor
                    TextEdit {
                        id: msgEdit
                        text: delegateRoot.msgText
                        x: msgRect.msgMargin
                        y: msgRect.msgMargin
                        width: parent.width - msgRect.msgMargin * 2
                        height: contentHeight
                        wrapMode: TextEdit.Wrap
                        selectByMouse: true
                    }
                }
            }
        }
    }
}
