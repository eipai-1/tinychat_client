#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <QJsonArray>
#include <QJsonObject>

using u64 = std::uint64_t;

template <typename T>
static std::vector<T> fromJsonArray(const QJsonArray& ja) {
    std::vector<T> result;
    result.reserve(ja.size());
    for (const auto& jo : ja) {
        result.push_back(T::fromJson(jo.toObject()));
    }
    return result;
}

#endif // TYPES_H
