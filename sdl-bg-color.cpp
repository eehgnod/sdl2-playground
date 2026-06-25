#include <SDL.h>
#include <iostream>

enum class Color
{
    Red,
    Green,
    Blue,
    Black
};

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL INIT ERROR : " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Spring 1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL Create Window Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "SDL Create Renderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    Color current = Color::Black;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_R:
                    current = Color::Red;
                    std::cout << "Red\n";
                    break;
                case SDL_SCANCODE_G:
                    current = Color::Green;
                    std::cout << "Green\n";
                    break;
                case SDL_SCANCODE_B:
                    current = Color::Blue;
                    std::cout << "Blue\n";
                    break;
                default:
                    break;
                }
            }
        }

        switch (current)
        {
        case Color::Red:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        case Color::Green:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;
        case Color::Blue:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
        case Color::Black:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}