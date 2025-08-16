#ifndef TINYCHAT_CLIENT_H
#define TINYCHAT_CLIENT_H

#include "core/app_controller.h"

namespace tcc {
namespace core {

class TinychatClient
{
public:
    TinychatClient();
    void run();

private:
    AppController controller_;

};

} // namespace core
} // namespace tcc

#endif // TINYCHAT_CLIENT_H
