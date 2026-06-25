#include <SDL.h>
#include <iostream>
#include <chrono>
#include <thread>

struct Vec2
{
    float x, y;
};

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Sprint2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Vec2 pos{400.0f, 300.0f};
    const float speed = 200.0f;

    bool running = true;
    bool heavyLoad = false;
    SDL_Event event;
    auto prevTime = std::chrono::high_resolution_clock::now();

    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float>(currentTime - prevTime).count();
        prevTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                heavyLoad = !heavyLoad;
                std::cout << "CPU load: " << (heavyLoad ? "ON" : "OFF")
                          << " dt: " << dt << "\n";
            }
        }

        if (heavyLoad)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        const Uint8 *keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W])
            pos.y -= speed * dt;
        if (keys[SDL_SCANCODE_S])
            pos.y += speed * dt;
        if (keys[SDL_SCANCODE_A])
            pos.x -= speed * dt;
        if (keys[SDL_SCANCODE_D])
            pos.x += speed * dt;

        if (pos.x < 0)
            pos.x = 0;
        if (pos.x > 750)
            pos.x = 750;
        if (pos.y < 0)
            pos.y = 0;
        if (pos.y > 550)
            pos.y = 550;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect rect{static_cast<int>(pos.x), static_cast<int>(pos.y), 50, 50};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int barWidth = static_cast<int>(dt * 3000);
        if (barWidth > 800)
            barWidth = 800;
        SDL_Rect dtBar{0, 0, barWidth, 10};
        SDL_RenderFillRect(renderer, &dtBar);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}