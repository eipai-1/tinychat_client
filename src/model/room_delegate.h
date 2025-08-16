#ifndef ROOM_DELEGATE_H
#define ROOM_DELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

namespace tcc {
namespace model {
class RoomDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit RoomDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}  // namespace model
}  // namespace tcc

#endif  // ROOM_DELEGATE_H
