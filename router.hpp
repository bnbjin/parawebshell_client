#pragma once

#include <string>
#include <memory>
#include <functional>
#include <mutex>

#include "mod_proto.hpp"
#include "comm_wrapper.hpp"


namespace pws {

typedef std::function<void(int, std::string)> resp_handler;

class router
{
    router(const router&) = delete;
    router(const router&&) = delete;
    router& operator=(const router&) = delete;
    router&& operator=(const router&&) = delete;

public:

    router(const std::string &host, const std::string &port);

    ~router();

    bool init();

    void free();

    bool post(module_type mod, const std::string &json_cont);

    /*
    ret:    0   succeeded
            -1  failed, the handler of the specified module is existed
    */
    int reg_resp_handler(module_type mod, resp_handler handler);

private:

    std::shared_ptr<comm_wrapper>  _comm_wrapper_ptr;
};

}
