#include <boost/asio.hpp>

#include <iostream>

namespace asio = boost::asio;

const int SERVER_PORT = 3333;
const uint16_t READ_BUF_SIZE = 100;

int main() {
    try {
        asio::io_context ios;

        asio::ip::tcp::acceptor acceptor(
            ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), SERVER_PORT));

        asio::ip::tcp::socket sock = acceptor.accept();

        std::string req(READ_BUF_SIZE, '\0');
        size_t bytes_read = sock.read_some(asio::buffer(req));
        req.resize(bytes_read);

        std::cout << "Request from client: " << req << "\n";

        const std::string rsp = "Message received!";
        std::cout << "Sending response: " << rsp << "\n";
        asio::write(sock, asio::buffer(rsp));
    } catch (boost::system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
        return e.code().value();
    }

    return 0;
}
