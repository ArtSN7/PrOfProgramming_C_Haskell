#include "types.h"
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

// Some constants for better code readability
#define GRID_FREE 0
#define GRID_OBSTACLE 1
#define GRID_MARKER 2

// Initialize all cells in arena to free space
static void init_grid(Arena *arena)
{
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            arena->grid[i][j] = GRID_FREE;
        }
    }
}

// Calculate squared distance from a point to center, based on Pyth. theorem
static int distance_from_center_squared(int x, int y, int center_x, int center_y)
{
    int dx = x - center_x;
    int dy = y - center_y;
    return dx * dx + dy * dy;
}

/**
 * Place items randomly on grid
 * Keep trying random positions until it fins the valid one found
 * is_valid function is only needed for stage 5 ( last stage in the task with circle arena )
 * count - number of items to place
 * item_type - GRID_OBSTACLE or GRID_MARKER
 */
static void place_items_randomly(Arena *arena, int count, int item_type,
                                 bool (*is_valid)(int, int, Arena *))
{
    int placed = 0;

    while (placed < count)
    {
        // Generate random x,y coordinates
        int x = rand() % arena->width;
        int y = rand() % arena->height;

        // Check if cell is free
        if (arena->grid[y][x] == GRID_FREE &&
            (is_valid == NULL || is_valid(x, y, arena)))
        {
            arena->grid[y][x] = item_type; // place item
            placed++;
        }
    }
}

/**
 * Check if position is inside the inner free circle
 * Used for only place markers in center - only needed for stage 5 ( last stage in the task with circle arena )
 */
static bool is_in_inner_circle(int x, int y, Arena *arena)
{
    int center_x = arena->width / 2;
    int center_y = arena->height / 2;
    int outer_radius = (arena->width < arena->height ? arena->width : arena->height) / 2;
    int inner_radius = outer_radius * 2 / 3;

    // Check if point is within inner circle
    return distance_from_center_squared(x, y, center_x, center_y) <= inner_radius * inner_radius;
}

// Generate circular arena pattern with ring of obstacles
static void generate_circular_pattern(Arena *arena)
{
    // Calculate center point
    int center_x = arena->width / 2;
    int center_y = arena->height / 2;

    // Calculate rad
    int outer_radius = (arena->width < arena->height ? arena->width : arena->height) / 2;
    int inner_radius = outer_radius * 2 / 3;
    int inner_radius_sq = inner_radius * inner_radius;
    int outer_radius_sq = outer_radius * outer_radius;

    // Loop through entire grid
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            // Calculate distance from current cell to center
            int dist_sq = distance_from_center_squared(j, i, center_x, center_y);

            // If outside inner circle, place obstacle
            if (dist_sq > inner_radius_sq)
            {
                arena->grid[i][j] = GRID_OBSTACLE;
            }
        }
    }
}

/**
 * Create and initialize arena in two modes: rectangular ( random ) or circular ( stage 5 / challenging part )
 */
Arena arena_create(int width, int height, int num_obstacles, int num_presents, bool is_circular)
{
    // Initialize arena structure with provided parameters
    Arena arena = {
        .width = width,
        .height = height,
        .number_of_obstacles = num_obstacles,
        .number_of_presents = num_presents,
        .is_circular = is_circular};

    init_grid(&arena);

    if (is_circular)
    {
        generate_circular_pattern(&arena);
        place_items_randomly(&arena, num_presents, GRID_MARKER, is_in_inner_circle); // need to pass is_in_inner_circle function pointer to only place markers in center
    }
    else
    {
        place_items_randomly(&arena, num_obstacles, GRID_OBSTACLE, NULL);
        place_items_randomly(&arena, num_presents, GRID_MARKER, NULL);
    }

    return arena;
}

// Check if position is valid for robot movement
bool arena_is_valid_position(Position pos, Arena *arena)
{
    return pos.x >= 0 && pos.x < arena->width &&       // Check x bounds
           pos.y >= 0 && pos.y < arena->height &&      // Check y bounds
           arena->grid[pos.y][pos.x] != GRID_OBSTACLE; // Check not obstacle
}

// Getter for cell value with bounds checking
int arena_get_cell(Position pos, Arena *arena)
{
    // Check if position is within bounds
    if (pos.x >= 0 && pos.x < arena->width && pos.y >= 0 && pos.y < arena->height)
    {
        return arena->grid[pos.y][pos.x];
    }
    return -1;
}

// Setter for cell value with bounds checking
void arena_set_cell(Position pos, int value, Arena *arena)
{
    // Only set if position is within bounds
    if (pos.x >= 0 && pos.x < arena->width && pos.y >= 0 && pos.y < arena->height)
    {
        arena->grid[pos.y][pos.x] = value;
    }
}

// Draw grid lines to show cell boundaries and box boundaries
static void draw_grid(Arena arena, DisplayConfig display)
{
    int total_width = arena.width * display.cell_size;
    int total_height = arena.height * display.cell_size;

    setLineWidth(1);
    setColour(gray);

    // Draw lines between columns
    for (int i = 1; i < arena.width; i++)
    {
        int x = display.offset_x + i * display.cell_size;
        drawLine(x, display.offset_y, x, display.offset_y + total_height);
    }

    // Draw lines between rows
    for (int i = 1; i < arena.height; i++)
    {
        int y = display.offset_y + i * display.cell_size;
        drawLine(display.offset_x, y, display.offset_x + total_width, y);
    }
}

// Draw all obstacles as black squares
static void draw_obstacles(Arena arena, DisplayConfig display)
{
    setColour(black);

    for (int i = 0; i < arena.height; i++)
    {
        for (int j = 0; j < arena.width; j++)
        {
            // If cell contains obstacle, draw it
            if (arena.grid[i][j] == GRID_OBSTACLE)
            {
                fillRect(display.offset_x + j * display.cell_size + 1, // i have added +1 as a margin for shadow effect
                         display.offset_y + i * display.cell_size + 1,
                         display.cell_size - 2,
                         display.cell_size - 2);
            }
        }
    }
}

// Draw arena background layer
void arena_draw_background(Arena arena, DisplayConfig display)
{

    int total_width = arena.width * display.cell_size;
    int total_height = arena.height * display.cell_size;

    setColour(black);
    setLineWidth(3);
    drawRect(display.offset_x, display.offset_y, total_width, total_height);

    // Draw grid lines and obstacles
    draw_grid(arena, display);
    draw_obstacles(arena, display);
}

// Draw arena foreground layer (dynamic elements)
void arena_draw_foreground(Arena arena, DisplayConfig display)
{
    setColour(green);

    for (int i = 0; i < arena.height; i++)
    {
        for (int j = 0; j < arena.width; j++)
        {
            // If cell contains marker, draw it as circle
            if (arena.grid[i][j] == GRID_MARKER)
            {
                // Calculate center of cell
                int center_x = display.offset_x + j * display.cell_size + display.cell_size / 2;
                int center_y = display.offset_y + i * display.cell_size + display.cell_size / 2;
                int radius = display.cell_size / 4;

                fillOval(center_x - radius, center_y - radius, radius * 2, radius * 2);
            }
        }
    }
}