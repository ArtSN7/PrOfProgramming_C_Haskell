#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265359

// Function to map mathematical coordinates to SDL pixel coordinates
void mapCoords(double x, double y, int *px, int *py, double xMin, double xMax, double yMin, double yMax)
{
    *px = (int)((x - xMin) / (xMax - xMin) * WINDOW_WIDTH);
    *py = (int)((yMax - y) / (yMax - yMin) * WINDOW_HEIGHT);
}

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Trigonometric Graphs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set background to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Define graph ranges
    double xMin = -2 * PI, xMax = 2 * PI;
    double yMin = -2, yMax = 2;

    // Draw x-axis (black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int x0, y0, x1, y1;
    mapCoords(xMin, 0, &x0, &y0, xMin, xMax, yMin, yMax);
    mapCoords(xMax, 0, &x1, &y1, xMin, xMax, yMin, yMax);
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);

    // Draw y-axis (black)
    mapCoords(0, yMin, &x0, &y0, xMin, xMax, yMin, yMax);
    mapCoords(0, yMax, &x1, &y1, xMin, xMax, yMin, yMax);
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);

    // Label x-axis (at -2π, -π, 0, π, 2π)
    double xTicks[] = {-2 * PI, -PI, 0, PI, 2 * PI};
    for (int i = 0; i < 5; i++)
    {
        int px, py;
        mapCoords(xTicks[i], 0, &px, &py, xMin, xMax, yMin, yMax);
        SDL_RenderDrawLine(renderer, px, py - 5, px, py + 5); // Tick mark
    }

    // Label y-axis (at -1, 0, 1)
    double yTicks[] = {-1, 0, 1};
    for (int i = 0; i < 3; i++)
    {
        int px, py;
        mapCoords(0, yTicks[i], &px, &py, xMin, xMax, yMin, yMax);
        SDL_RenderDrawLine(renderer, px - 5, py, px + 5, py); // Tick mark
    }

    // Plot sin(x) in red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (double x = xMin; x <= xMax; x += 0.01)
    {
        double y = sin(x);
        int px, py;
        mapCoords(x, y, &px, &py, xMin, xMax, yMin, yMax);
        SDL_RenderDrawPoint(renderer, px, py);
    }

    // Plot cos(x) in blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (double x = xMin; x <= xMax; x += 0.01)
    {
        double y = cos(x);
        int px, py;
        mapCoords(x, y, &px, &py, xMin, xMax, yMin, yMax);
        SDL_RenderDrawPoint(renderer, px, py);
    }

    // Plot tan(x) in green, avoiding large values
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (double x = xMin; x <= xMax; x += 0.01)
    {
        double y = tan(x);
        if (y > yMax || y < yMin)
            continue; // Skip points outside y-range
        int px, py;
        mapCoords(x, y, &px, &py, xMin, xMax, yMin, yMax);
        SDL_RenderDrawPoint(renderer, px, py);
    }

    // Update the screen
    SDL_RenderPresent(renderer);

    // Event loop to keep window open
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}