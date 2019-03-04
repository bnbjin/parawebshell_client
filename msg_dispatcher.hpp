#pragma once

#include <string>
#include <map>
#include <memory>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "mod_proto.hpp"
#include "pwsque.hpp"


namespace pws {

typedef std::function<int(mod_type, std::string)> mod_resp_handler;

class msg_dispatcher
{
    msg_dispathcer(msg_dispatcher&) = delete;
    msg_dispathcer(msg_dispatcher&&) = delete;
    msg_dispatcher& operator=(const msg_dispatcher&) = delete;
    msg_dispatcher&& operator=(const msg_dispatcher&&) = delete;

public:

    msg_dispatcher();

    ~msg_dispatcher();

    bool init();

    void free();

    bool send(module_type mod, const std::string &msg);

    /*
    ret:    0   succeeded
            -1  failed, the handler of the specified module is existed
    */
    int reg_resp_handler(module_type mod, mod_resp_handler handler);

private:

    std::shared_ptr<mod_comm_wrapper>   _mod_comm_wrapper;
    std::map<mod_type, module_addr>     _mod_addr_tab;
    // TODO to use read-write lock instead
    std::mutex                          _mod_addr_tab_mtx;
    // TODO to use protobuf instead of std::string
    pwsque<std::string>                 _out_que;
    pwsque<std::string>                 _in_que;
    std::vector<std::thread>            _thrs;
    std::mutex                          _stop_mtx;
    std::condition_variable             _stop_cv;
};

}
