#pragma once

struct Controls {
    float x = 0;
    float y = 0;
};

void initUdp();

void sendControls(Controls);

void setClientIp(const class IPAddress &ip);

