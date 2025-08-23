#ifndef ENUMS_H
#define ENUMS_H

#include <string_view>
#include <map>

#include <QString>

namespace tcc::utils {
enum class WSType : int {
    PrivateMsg = 1,
    GroupMsg = 2,
    MsgSent = 3,
    Invalid = 0,
};
inline QString ws_type_to_string(WSType type) {
    switch (type) {
        case WSType::PrivateMsg:
            return QString("private_message");
        case WSType::GroupMsg:
            return QString("group_message");
        case WSType::MsgSent:
            return QString("message_sent");
        default:
            return QString("invalid");  // Default case, can be adjusted as needed
    }
}

inline WSType string_to_ws_type(const QString& str) {
    static const std::map<QString, WSType> str_to_type_map = {
        {QString("private_message"), WSType::PrivateMsg},
        {QString("group_message"), WSType::GroupMsg},
        {QString("message_sent"), WSType::MsgSent},
    };
    auto it = str_to_type_map.find(str);
    if (it != str_to_type_map.end()) {
        return it->second;
    }
    return WSType::Invalid;  // Return Invalid if the string does not match any type
}
}  // namespace tcc::utils

#endif  // ENUMS_H
