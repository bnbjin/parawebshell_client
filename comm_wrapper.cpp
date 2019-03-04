#include "comm_wrapper.hpp"

using namespace std;


namespace pws {

comm_wrapper::comm_wrapper(const string &host, const string &port)
:   _host(host), _port(port)
,   _resp_handler_map()
,   _resp_handler_map_mtx()
{}


virtual
comm_wrapper::~comm_wrapper()
{}


int comm_wrapper::reg_resp_handler(module_type mod, resp_handler handler)
{
    // TODO: to change to be a read-write lock
    lock_guard<mutex> lck(_resp_handler_map_mtx);

    if (_resp_handler_map::end() != _resp_handler_map.find(mod))
        return -1; 

    _resp_handler_map[mod] = handler;

    return 0;
}

void comm_wrapper::heart_beat_sender()
{
    
}

}
