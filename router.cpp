#include "router.hpp"

using namespace std;


namespace pws {


router::router(const string &host, const string &port)
:   _comm_ptr(new COMM_TYPE(host, port))
{}


router::~router() {}


bool router::init()
{
    return _comm_ptr->init();
}


void router::free() 
{
    _comm_ptr->free();
}


bool router::post(module_type mod, const string &json_cont)
{
    return _comm_ptr->post_log(mod, json_cont);
}


int router::reg_resp_handler(module_type mod, resp_handler handler)
{
    return _comm_ptr->reg_resp_handler(mod, handler);
}


}
