#include "chat_msg_edit.h"

#include <QKeyEvent>

namespace tcc::ui {
ChatMsgEdit::ChatMsgEdit(QWidget* parent) : QTextEdit(parent) {}
void ChatMsgEdit::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 当同时按下Ctrl和Enter时
        if (event->modifiers() & Qt::ControlModifier) {
            //qDebug() << "Ctrl+Enter pressed";
            emit ctrlEnterPressed(toPlainText());
            clear();
        }
    }
    QTextEdit::keyPressEvent(event);
}
}  // namespace tcc::ui
