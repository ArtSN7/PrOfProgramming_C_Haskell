#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "graphics.h"

/**
 * Setup display window and draw background layer
 * Background contains static elements: grid, obstacles
 */
static void setup_display(Arena arena, DisplayConfig display)
{
    setWindowSize(arena.width * display.cell_size + 100,
                  arena.height * display.cell_size + 100);

    background();
    clear();

    // Fill entire window with white background
    setColour(white);
    fillRect(0, 0, arena.width * display.cell_size + 100,
             arena.height * display.cell_size + 100);

    // Draw arena grid and obstacles
    arena_draw_background(arena, display);
}

/**
 * Draw initial foreground layer
 * Foreground contains dynamic elements: markers, robot
 */
static void initial_draw(Arena arena, Robot robot, DisplayConfig display)
{
    // Switch to foreground layer
    foreground();
    clear();

    // Draw dynamic elements
    arena_draw_foreground(arena, display);
    robot_draw(robot, display);
}

// Function used to show completion message
static void show_completion(Robot robot, Arena arena)
{
    char msg[100];

    // Check if all markers were collected
    if (markerCount(&robot) == arena.number_of_presents)
    {
        sprintf(msg, "Mission Complete! Collected %d markers", markerCount(&robot));
    }

    message(msg);
}

// Print information on arguments passed to the program
static void print_usage(char *program_name)
{
    fprintf(stderr, "Usage: %s <width> <height> <obstacles> <presents> <is_circular>\n", program_name);
    fprintf(stderr, "Example: %s 20 20 50 10 0 | java -jar drawapp-4.5.jar\n", program_name);
    fprintf(stderr, "Example: %s 30 30 0 15 1 | java -jar drawapp-4.5.jar (circular)\n", program_name);
    fprintf(stderr, "\nParameters:\n");
    fprintf(stderr, "  width, height  - Arena dimensions (1-50)\n");
    fprintf(stderr, "  obstacles      - Number of obstacles (ignored if circular)\n");
    fprintf(stderr, "  presents       - Number of markers to collect\n");
    fprintf(stderr, "  is_circular    - 0=rectangular, 1=circular\n");
}

/**
 * Validate command line arguments
 * Returns false if any argument is invalid
 */
static bool validate_args(int width, int height, int obstacles, int presents,
                          int is_circular, char *program_name)
{
    if (width < 1 || width > 50 || height < 1 || height > 50)
    {
        fprintf(stderr, "Error: Dimensions must be 1-50\n");
        print_usage(program_name);
        return false;
    }

    if (obstacles < 0 || presents < 0)
    {
        fprintf(stderr, "Error: Counts must be non-negative\n");
        print_usage(program_name);
        return false;
    }

    if (is_circular != 0 && is_circular != 1)
    {
        fprintf(stderr, "Error: is_circular must be 0 or 1\n");
        print_usage(program_name);
        return false;
    }

    // For rectangular arena, check total items fit in arena
    if (!is_circular && obstacles + presents > width * height - 1)
    {
        fprintf(stderr, "Error: Too many items for %dx%d arena\n", width, height);
        return false;
    }

    return true;
}

// Main function - entry point of program , AKA brain
int main(int argc, char *argv[])
{
    srand(time(NULL)); // initialize random seed

    // Check correct number of arguments
    if (argc != 6)
    {
        print_usage(argv[0]);
        return 1;
    }

    // Parse command line arguments
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int num_obstacles = atoi(argv[3]);
    int num_presents = atoi(argv[4]);
    int is_circular = atoi(argv[5]);

    // Validate arguments
    if (!validate_args(width, height, num_obstacles, num_presents, is_circular, argv[0]))
    {
        return 1;
    }

    // Create objects
    Arena arena = arena_create(width, height, num_obstacles, num_presents, (bool)is_circular);
    DisplayConfig display = {.cell_size = 30, .offset_x = 50, .offset_y = 50};
    Robot robot = robot_create(&arena);

    // Setup graphics
    setup_display(arena, display);
    initial_draw(arena, robot, display);
    sleep(500); // just for a better UX I set up pause

    // Run robot-movement-logic
    robot_explore_all(&robot, &arena, display);

    show_completion(robot, arena);

    return 0;
}