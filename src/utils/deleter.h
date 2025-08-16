#ifndef DELETER_H
#define DELETER_H

#include <QObject>

namespace tcc {
namespace utils {

struct QObjectDeleter
{
    void operator() (QObject* obj) {
        if (obj) {
            obj->deleteLater();
        }
    }
};

} // namespace utils
} // namespace tcc

#endif // DELETER_H
