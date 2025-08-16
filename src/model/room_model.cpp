#include "room_model.h"

namespace tcc {
namespace model {
RoomModel::RoomModel(QObject *parent) : QAbstractListModel{parent} {}
QVariant RoomModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    const Room &room = rooms_.at(index.row());

    if (role == RoomRole) {
        return QVariant::fromValue(room);
    }

    //?
    if (role == Qt::DisplayRole) {
        return room.name;
    }

    return QVariant();
}
void RoomModel::addRoom(const tcc::model::Room &room) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    rooms_.append(room);
    endInsertRows();
}
}  // namespace model
}  // namespace tcc
