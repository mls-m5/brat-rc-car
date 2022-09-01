#include "guiudp.h"
#include "sdlpp/events.hpp"
#include "sdlpp/render.hpp"
#include "sdlpp/window.hpp"
#include <Arduino.h>
#include <iostream>
#include <thread>

void pinMode(int pin, int value) {}

int analogRead(int pin) {
    return 0;
}

void analogWrite(int pin, int value) {}

void delay(int value) {
    using namespace std::literals;
    std::this_thread::sleep_for(value * 1ms);
}

void digitalWrite(int pin, int value) {}

int main(int argc, char *argv[]) {
    auto width = 400;
    auto height = 400;
    auto window = sdl::Window{"rc car simulator gui",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN};

    auto renderer = sdl::Renderer{window, -1, SDL_RENDERER_ACCELERATED};

    float x = .1;
    float y = .1;

    float maxX = -1000;
    float minX = 1000;
    float maxY = -1000;
    float minY = 1000;

    auto thread = std::thread{[&]() {
        startServer([&](auto nx, auto ny) {
            //            x = nx / 2000. - 1.; // TODO: Make some sensible
            //            normalization
            x = nx;
            //            y = ny / 2000. - 1.;
            y = ny;

            if (x < minX) {
                minX = x;
                std::cout << "min x " << nx << std::endl;
            }
            if (x > maxX) {
                maxX = x;
                std::cout << "max x " << nx << std::endl;
            }
            if (y < minY) {
                minY = y;
                std::cout << "min y " << ny << std::endl;
            }
            if (y > maxY) {
                maxY = y;
                std::cout << "max y " << ny << std::endl;
            }

            x = std::max(x, -1.f);
            x = std::min(x, 1.f);
            y = std::max(y, -1.f);
            y = std::min(y, 1.f);
        });
    }};

    for (auto running = true; running;) {
        for (std::optional<sdl::Event> event; (event = sdl::pollEvent());) {
            if (event->type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        renderer.drawColor({10, 0, 0});
        renderer.fillRect();
        renderer.drawColor({100, 0, 0});

        renderer.drawLine(width / 2, 0, width / 2, height);
        renderer.drawLine(0, height / 2, width, width / 2);

        float px = (width / 2) * (1. + x);
        float py = (height / 2) * (1. + y);

        renderer.drawColor({255, 255, 255});

        renderer.drawLine(px - 10, py - 10, px + 10, py + 10);
        renderer.drawLine(px + 10, py - 10, px - 10, py + 10);

        renderer.present();
    }

    stopServer();

    thread.join();

    return 0;
}
