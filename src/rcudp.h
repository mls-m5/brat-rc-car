#pragma once

struct Controls {
    float x = 0;
    float y = 0;
};

void initUdp(bool isAp);

void sendControls(Controls);

void setClientIp(const class IPAddress &ip);

