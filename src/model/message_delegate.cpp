#include <QPainter>

#include "model/message_delegate.h"
#include "model/message_model.h"
#include "model/message.h"

using Message = tcc::model::Message;

namespace tcc::model{
MessageDelegate::MessageDelegate(QObject *parent) : QStyledItemDelegate{parent} {}

void MessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {
    painter->save();

    painter->fillRect(option.rect, QColor(240, 248, 255));

    Message message = index.data(static_cast<int>(MessageModel::Role::Complete)).value<Message>();

    int padding = 4;
    QRect textRect = option.rect.adjusted(padding, 0, -padding, 0);

    //qDebug() << "Drawing text:" << message.content;

    if (index.data(static_cast<int>(MessageModel::Role::IsMe)).toBool()) {
        painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, message.content);
    } else {
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, message.content);
    }

    painter->restore();
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {
    return QSize(200, 35);
}
}
