#include "http_wrapper.hpp"

#include <thread>


using namespace std;

namespace pws {


http_wrapper::http_wrapper(const string &host, const string port)
:   _ptr(new http(host, port))
{}

virtual
http_wrapper::~http_wrapper()
{}

virtual bool init()
{
    // TODO add heart beat thread  

    return true;
}

virtual void free()
{

}


}
