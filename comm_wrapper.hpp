#pragma once

#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <functional>
#include <thread>
#include <atomic>

#include "mod_proto.hpp"


namespace pws {

typedef std::function<bool(int, const std::string&)> resp_handler;

/*
design pattern:
    * strategy
    * observer alike
*/
class comm_wrapper
{
    comm_wrapper(const comm_wrapper&) = delete;
    comm_wrapper(const comm_wrapper&&) = delete;
    comm_wrapper& operator=(const comm_wrapper&) = delete;
    comm_wrapper&& operator=(const comm_wrapper&&) = delete;

public:

    comm_wrapper(const std::string &host, const std::string &port);

    virtual ~comm_wrapper();

    virtual bool init() = 0;

    virtual void free() = 0;

    virtual bool post_log(module_type mod, const std::string &json) = 0;

    /*
    ret:    0   succeeded
            -1  failed, the handler of the specified module is existed
    */
    int reg_resp_handler(module_type mod, resp_handler handler);
    
protected:
    
    virtual bool send_heart_beat() = 0;

    void heart_beat_sender();

protected:

    /* host address */
    std::string                         _host;
    std::string                         _port;

    /* handler map */
    std::map<module_type, resp_handler> _resp_handler_map;
    std::mutex                          _resp_handler_map_mtx;

    /* resp handler thread pool */
    unsigned int                        _thr_count;
    std::vector<std::thread>            _thrs;
    std::atomic<bool>                   _stop_signal;
};

}
