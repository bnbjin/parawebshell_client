#include "http.hpp"

#include <iostream>
#include <deque>


namespace pws {

using namespace std;
using boost::asio::ip::tcp;


static bool
test_net_env(
    boost::asio::io_context &io_context,
    const string &host, 
    const string &port
)
{
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::query query(host, port);
    boost::asio::ip::tcp::resolver::iterator endpoint_iter = resolver.resolve(query);

    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoint_iter);

    return true;
}

int post(
    boost::asio::io_context &io_context,
    const string &host, 
    const string &port, 
    const string &page, 
    const string &data,
    string &response_data
)
try
{
    if (io_context.stopped())
        io_context.reset(); 

    if (!test_net_env(io_context, host, port))
        return -1;
    
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "POST" << page << "HTTP/1.0\r\n";
    request_stream << "Host: " << host << ":" << port << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Content-Length: " << data.length() << "\r\n";
    request_stream << "Content-Type: application/x-www-form-urlencoded\r\n";
    request_stream << "Connection: close\r\n\r\n";
    request_stream << data;

    boost::asio::write(socket, request);

    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");
    istream response_stream(&response);
    
    string http_version;
    response_stream >> http_version;

    unsigned int status_code;
    response_stream >> status_code;

    string status_message;
    getline(response_stream, status_message);

    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
        response_data = "Invalid response";
        return -1;
    }

    if (status_code != 200)
    {
        response_data = "Response returned with status code != 200 " ;
        return status_code;
    }

    /* reading headers of response */
    std::string header;
    std::vector<string> headers;        
    while (std::getline(response_stream, header) && header != "\r")
    {
        headers.push_back(header);
    }

    /* reading body of response */
    boost::system::error_code error;
    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error));

    if (response.size())
    {
        std::istream response_stream(&response);
        std::istreambuf_iterator<char> eos;
        response_data = string(std::istreambuf_iterator<char>(response_stream), eos);                        
    }

    if (error != boost::asio::error::eof)
    {
        response_data = error.message();
        return -1;
    }

    return 0;
}
catch (...)
{
    throw;
    // TODO: replace with specific exception handling
}

/* http definition */
http::http(const string &host, const string &port)
:   _msg_que(32)
{

}

http::~http() {}


/* router */
}
