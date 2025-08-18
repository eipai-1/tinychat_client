#ifndef MESSAGE_MODEL_H
#define MESSAGE_MODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QHash>

#include "model/message.h"
#include "utils/types.h"

namespace tcc::model {
class MessageModel : public QAbstractListModel {
public:
    explicit MessageModel(QObject *parent, u64 cur_user_id);
    explicit MessageModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}

    enum class Role : int {
        Complete = Qt::UserRole + 1,
        IsMe,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return messages_[cur_room_id_].size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addMessageByRoom(const QList<tcc::model::Message> &msgs);

    void setCurRoom(u64 new_cur_room) {
        if (cur_room_id_ == new_cur_room) return;
        beginResetModel();
        cur_room_id_ = new_cur_room;
        endResetModel();
    }

private:
    QHash<u64, QList<tcc::model::Message>> messages_;
    u64 cur_user_id_;
    u64 cur_room_id_;
};
}  // namespace tcc::model

#endif  // MESSAGE_MODEL_H
