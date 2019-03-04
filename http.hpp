#pragma once

#include <vector>
#include <string>

#include <boost/asio.hpp>

#include "pwsque.hpp"


namespace pws {

int post(
    boost::asio::io_context &io_context,
    const std::string &host, 
    const std::string &port, 
    const std::string &page, 
    const std::string &data,
    std::string &response_data
);

typedef std::vector<unsigned char> msg_t;

class http
{
    http(const http&) = delete;
    http(const http&&) = delete;
    http& operator=(const http&) = delete;
    http&& operator=(const http&&) = delete;

public:
    http(const std::string &host, const std::string &port);

    ~http();

    int get();

    int post();

    // TODO: to implement the rest of http operation when needed

protected:
    
private:
    pwsque<msg_t>       _msg_que;
};

}
