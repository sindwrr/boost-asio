#include <boost/asio.hpp>

#include <iostream>

namespace asio = boost::asio;

const std::string SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 3333;
const uint16_t READ_BUF_SIZE = 100;

int main() {
    try {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SERVER_IP),
                                   SERVER_PORT);

        asio::io_context ios;
        asio::ip::tcp::socket sock(ios, ep.protocol());
        sock.connect(ep);

        const std::string req = "Hello server!";
        std::cout << "Sending request: " << req << "\n";
        asio::write(sock, asio::buffer(req));

        std::string rsp(READ_BUF_SIZE, '\0');
        size_t bytes_read = sock.read_some(asio::buffer(rsp));
        rsp.resize(bytes_read);

        std::cout << "Response from server: " << rsp << "\n";
    } catch (boost::system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
        return e.code().value();
    }


    return 0;
}
