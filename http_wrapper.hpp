#pragma once

#include <memory>

#include "mod_proto.hpp"
#include "comm_wrapper.hpp"
#include "http.hpp"


namespace pws {

class http_wrapper : public comm_wrapper
{
    http_wrapper(const http_wrapper&) = delete;
    http_wrapper(const http_wrapper&&) = delete;
    http_wrapper& operator=(const http_wrapper&) = delete;
    http_wrapper&& operator=(const http_wrapper&&) = delete;

public:
    
    http_wrapper(const std::string &host, const std::string &port);
    
    virtual ~http_wrapper();

    virtual bool init();

    virtual void free();

    virtual bool post_log(module_type mod, const std::string &json);

private:

    bool connect();

    void disconnect();

    virtual bool send_heart_beat();

    std::shared_ptr<http>   _ptr;
};

}
