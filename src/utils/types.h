#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>

using u64 = std::uint64_t;
constexpr u64 U64_MAX = std::numeric_limits<u64>::max();

template <typename T>
static std::vector<T> fromJsonArray(const QJsonArray& ja) {
    std::vector<T> result;
    result.reserve(ja.size());
    for (const auto& jo : ja) {
        result.push_back(T::fromJson(jo.toObject()));
    }
    return result;
}

template <typename T>
static QList<T> jsonArrayToQList(const QJsonArray& ja) {
    QList<T> result;
    result.reserve(ja.size());
    for (const auto& jo : ja) {
        result.append(T::fromJson(jo.toObject()));
    }
    return result;
}

#endif  // TYPES_H
