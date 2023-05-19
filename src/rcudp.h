#pragma once

struct Controls {
    float x = 0;
    float y = 0;

    void normalize() {
        if (x < -1.f) {
            x = -1.f;
        }
        else if (x > 1.) {
            x = 1.f;
        }

        if (y < -1.f) {
            y = -1.f;
        }
        else if (y > 1.) {
            y = 1.f;
        }
    }
};

void initUdp(bool isAp, bool isCar);

void sendControls(Controls);

void setClientIp(const class IPAddress &ip);

bool readUdp(Controls &controls);