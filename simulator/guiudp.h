#pragma once
#include <functional>

using UdpFunctionT = std::function<void(float x, float y)>;

void startServer(UdpFunctionT);
void stopServer();
