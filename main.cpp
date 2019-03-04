#include <iostream>
#include <exception>
#include <thread>

#include <boost/asio.hpp>
#include <boost/stacktrace.hpp>

#include <signal.h>

#include "http.hpp"
#include "router.hpp"


using namespace std;
using namespace pws;


int main(int argc, char *argv[])
try 
{
    boost::asio::io_context io_context;
    thread t([&io_context](){ io_context.run(); });
    
    /* setting signal's thing */
    struct sigaction oact_int = { 0 };
    struct sigaction oact_term = { 0 };

    int res_int = ::sigaction(SIGINT, NULL, &oact_int);
    int res_term = ::sigaction(SIGTERM, NULL, &oact_term);

    /* do the thing */
    router<http> rtr("wttr.in", "80");
    
    return 0;
}
catch (exception &e)
{
    cerr << e.what() << endl;
    cerr << boost::stacktrace::stacktrace();

    return -1;
}
catch (...)
{
    cerr << "Unknown exception caught while posting http request." << endl;
    cerr << boost::stacktrace::stacktrace();
        
    return -1;
}
