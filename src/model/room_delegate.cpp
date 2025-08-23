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
    // 暂存painter状态，再函数最后使用restore恢复，可以确保对painter的修改不会影响其他绘制
    painter->save();

    // 当前项状态是否包含了被选中这个标志
    if (option.state & QStyle::State_Selected) {
        // option.rect是当前项可以绘制的全部矩形区域
        // option.palette.highlight() 从系统调色板中获取高亮颜色，使应用颜色与系统主题一致
        painter->fillRect(option.rect, option.palette.highlight());
    } else {
        painter->fillRect(option.rect, QColor(240, 248, 255));  // AliceBlue
    }

    Room room = index.data(static_cast<int>(RoomModel::Role::Complete)).value<Room>();

    // painter->setPen(option.state & QStyle::State_Selected ?
    // option.palette.highlightedText().color()
    //                                                       : option.palette.text().color());

    painter->setPen(QColor(255, 0, 0));

    int padding = 5;

    // 这个矩形用于文本绘制，让不同项文本不会紧贴在一起
    QRect textRect = option.rect.adjusted(padding, 0, -padding, 0);

    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, room.name);

    painter->restore();
}

// 这个函数告诉List每个项的大小
QSize RoomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(100, 40);
}
}  // namespace model
}  // namespace tcc
