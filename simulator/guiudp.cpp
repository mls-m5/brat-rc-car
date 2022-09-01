#include "guiudp.h"
#include <boost/asio.hpp>
#include <sstream>

namespace {
bool running = true;
}

void startServer(UdpFunctionT f) {
    using udp = boost::asio::ip::udp;

    const auto port = 8088;

    auto service = boost::asio::io_service{};
    auto socket = udp::socket{
        service, udp::endpoint{udp::v4(), static_cast<unsigned short>(port)}};

    while (running) {
        auto buffer = std::array<char, 100>{};
        auto remoteEndpoint = udp::endpoint{};
        auto error = boost::system::error_code{};

        auto size = socket.receive_from(
            boost::asio::buffer(buffer), remoteEndpoint, 0, error);

        if (error && error != boost::asio::error::message_size) {
            throw boost::system::system_error{error};
        }

        auto ss = std::istringstream{std::string{buffer.data(), size}};

        float x = 0;
        float y = 0;

        ss >> x >> y;

        f(x, y);
    }
}

void stopServer() {
    running = false;
}
