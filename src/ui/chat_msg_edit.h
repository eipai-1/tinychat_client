#ifndef CHAT_MSG_EDIT_H
#define CHAT_MSG_EDIT_H

#include <QTextEdit>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ChatMsgEdit;
}
QT_END_NAMESPACE

namespace tcc::ui {
class ChatMsgEdit : public QTextEdit {
    Q_OBJECT
public:
    ChatMsgEdit(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void ctrlEnterPressed(const QString& text);
};
}  // namespace tcc::ui
#endif  // CHAT_MSG_EDIT_H
