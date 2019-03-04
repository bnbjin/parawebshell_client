#include "msg_dispatcher.hpp"

namespace pws {

msg_dispatcher::msg_dispatcher()
:   _mod_comm_wrap()
,   _mod_addr_tab()
,   _mod_addr_tab_()
,   _out_que()
,   _in_que()
,   _thrs()
,   _stop_mtx()
,   _stop_cv()
{}

msg_dispatcher::~msg_dispatcher()
{}

/*
1. luanch consumer threads
1.1. 1 consumer of consuming out queue(from dispatcher to module)
1.2. 2 consumer of consuming in queue(from module to dispatcher)
2. luanch module communication server
*/
bool msg_dispatcher::init()
{
    return true;
}

/*
1. stop module communication server
2. stop consumer threads
*/
void msg_dispatcher::free()
{}

}
