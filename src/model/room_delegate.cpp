#include <QPainter>

#include "model/room.h"
#include "model/room_delegate.h"
#include "model/room_model.h"

using Room = tcc::model::Room;

namespace tcc {
namespace model {
RoomDelegate::RoomDelegate(QObject *parent) : QStyledItemDelegate{parent} {}

void RoomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const {
    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    } else {
        painter->fillRect(option.rect, QColor(240, 248, 255));  // AliceBlue
    }

    Room room = index.data(RoomModel::Role::RoomRole).value<Room>();

    // painter->setPen(option.state & QStyle::State_Selected ?
    // option.palette.highlightedText().color()
    //                                                       : option.palette.text().color());

    painter->setPen(QColor(255, 0, 0));

    int padding = 5;
    QRect textRect = option.rect.adjusted(padding, 0, -padding, 0);

    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, room.name);

    painter->restore();
}

QSize RoomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(100, 40);
}
}  // namespace model
}  // namespace tcc
