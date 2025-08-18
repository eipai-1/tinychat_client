#include "model/message_model.h"

using Message = tcc::model::Message;

namespace tcc::model {
MessageModel::MessageModel(QObject *parent, u64 cur_user_id)
    : QAbstractListModel{parent}, cur_user_id_{cur_user_id} {}

QVariant MessageModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (!messages_.contains(cur_room_id_)) {
        return QVariant();
    }
    const Message &message = messages_[cur_room_id_].at(index.row());

    if (role == static_cast<int>(Role::Complete)) {
        return QVariant::fromValue(message);
    }

    if (role == Qt::DisplayRole) {
        return message.content;
    }

    if (role == static_cast<int>(Role::IsMe)) {
        return message.sender_id == cur_user_id_;
    }

    return QVariant();
}

void MessageModel::addMessageByRoom(const QList<Message> &msgs) {
    if (msgs.empty()) {
        return;
    }
    u64 room_id = msgs[0].room_id;

    if (room_id == cur_room_id_) {
        int firstRowToInsert = messages_[cur_room_id_].size();
        //    结束的行号是加上新消息数量之后的位置
        int lastRowToInsert = firstRowToInsert + msgs.size() - 1;

        // 2. 发射 beginInsertRows() 信号
        //    参数：
        //    - parent: 对于列表模型，总是 QModelIndex()
        //    - first:  要插入的第一行的索引
        //    - last:   要插入的最后一行的索引
        beginInsertRows(QModelIndex(), firstRowToInsert, lastRowToInsert);

        // 3. 在 begin 和 end 之间，安全地修改你的内部数据
        messages_[cur_room_id_].append(msgs);

        // 4. 发射 endInsertRows() 信号
        //    这个信号会告诉视图：“插入完成了，请更新界面吧！”
        //    视图会自动为新行请求数据并重绘，甚至可以支持动画效果。
        endInsertRows();
    } else {
        messages_[room_id].append(msgs);
    }
}
}  // namespace tcc::model
