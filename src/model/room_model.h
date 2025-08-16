#ifndef ROOM_MODEL_H
#define ROOM_MODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "model/room.h"

namespace tcc {
namespace model {
class RoomModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit RoomModel(QObject *parent = nullptr);

    enum Role {
        RoomRole = Qt::UserRole + 1,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return 0;  // No children for any item
        }
        return rooms_.count();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addRoom(const tcc::model::Room &room);

private:
    QList<tcc::model::Room> rooms_;
};
}  // namespace model
}  // namespace tcc

#endif  // ROOM_MODEL_H
