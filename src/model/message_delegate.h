#ifndef MESSAGE_DELEGATE_H
#define MESSAGE_DELEGATE_H

#include <QStyledItemDelegate>

namespace  tcc::model {

class MessageDelegate : public QStyledItemDelegate {
public:
    explicit MessageDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}
#endif  // MESSAGE_DELEGATE_H
