#include "sdlpp/events.hpp"
#include "sdlpp/render.hpp"
#include "sdlpp/window.hpp"
#include <Arduino.h>
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
    auto window = sdl::Window{"rc car simulator gui",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              800,
                              600,
                              SDL_WINDOW_SHOWN};

    auto renderer = sdl::Renderer{window, -1, SDL_RENDERER_ACCELERATED};

    for (auto running = true; running;) {
        renderer.drawColor({255, 255, 255});
        renderer.fillRect();
        for (std::optional<sdl::Event> event; (event = sdl::pollEvent());) {
            if (event->type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        window.swap();
    }

    return 0;
}
