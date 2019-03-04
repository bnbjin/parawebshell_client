#pragma once

namespace pws {

enum module_type
{
    system,
    process,
    file,
    net
};


struct module_addr
{
    std::string port;
};

}
