#include "types.h"
#include <stdlib.h>
#include "graphics.h"

/**
 * Find a random free position in the arena
 * Keep trying until free cell found
 */
static Position find_random_free_position(Arena *arena)
{
    Position pos;
    do
    {
        // Generate random coordinates
        pos.x = rand() % arena->width;
        pos.y = rand() % arena->height;
    } while (arena->grid[pos.y][pos.x] != GRID_FREE); // Repeat if not free

    return pos;
}

// Create robot at random free position
Robot robot_create(Arena *arena)
{
    Robot robot = {
        .pos = find_random_free_position(arena), // Random start position
        .direction = DIR_UP,                     // Start facing up
        .picked_markers = 0};                    // Start with no markers
    return robot;
}

/**
 * Calculate the position robot would move to if going forward
 * Doesn't actually move the robot, just calculates the position for the future
 */
Position robot_get_next_position(Robot *robot)
{
    Position next = robot->pos; // Start with current position

    // Modify next position based on direction
    switch (robot->direction)
    {
    case DIR_UP:
        next.y--; // Moving up decreases y
        break;
    case DIR_RIGHT:
        next.x++; // Moving right increases x
        break;
    case DIR_DOWN:
        next.y++; // Moving down increases y
        break;
    case DIR_LEFT:
        next.x--; // Moving left decreases x
        break;
    }

    return next;
}

/**
 * Move robot forward one tile in current direction
 * Only moves if next position is valid (in bounds and not obstacle)
 * If obstacle or wall ahead, robot doesn't move
 */
void forward(Robot *robot, Arena *arena)
{
    Position next = robot_get_next_position(robot);

    // Check if the next position is free basically
    if (arena_is_valid_position(next, arena))
    {
        robot->pos = next; // Move robot
    }
}

void right(Robot *robot)
{
    robot->direction = (robot->direction + 1) % 4;
}

/**
 * Checks if robot is currently on a marker tile
 * return 1 if on marker, 0 otherwise
 */
int atMarker(Robot *robot, Arena *arena)
{
    return arena_get_cell(robot->pos, arena) == GRID_MARKER;
}

/**
 * Check if robot can move forward without hitting obstacle or wall
 * 1 (true) if can move, 0 if nah
 */
int canMoveForward(Robot *robot, Arena *arena)
{
    // Calculate next position and check if valid
    Position next = robot_get_next_position(robot);
    return arena_is_valid_position(next, arena);
}

/**
 * Pick up marker from current tile if it is the index with a marker
 * Marker is then removed from grid
 * Nothing happens if no marker present
 */
void pickUpMarker(Robot *robot, Arena *arena)
{
    // Check if on marker
    if (atMarker(robot, arena))
    {
        // Remove marker from grid
        arena_set_cell(robot->pos, GRID_FREE, arena);
        robot->picked_markers++; // just increment picked markers
    }
}

/**
 * Drop one marker on current tile
 * Used only in the end in the corner
 */
void dropMarker(Robot *robot, Arena *arena)
{
    // Check if robot has markers and tile is free
    if (robot->picked_markers > 0 && arena_get_cell(robot->pos, arena) == GRID_FREE)
    {
        // Place marker on grid
        arena_set_cell(robot->pos, GRID_MARKER, arena);
        robot->picked_markers = 0; // drop all markers
    }
}

// Get number of markers robot is carrying
int markerCount(Robot *robot)
{
    return robot->picked_markers;
}

// Draw robot
static void draw_robot_body(Position pos, int cell_size, int offset_x, int offset_y)
{
    // Calculate center of robot's cell
    int center_x = offset_x + pos.x * cell_size + cell_size / 2;
    int center_y = offset_y + pos.y * cell_size + cell_size / 2;
    int radius = cell_size / 3;
    setColour(blue);
    fillOval(center_x - radius, center_y - radius, radius * 2, radius * 2);
}

// Draw red line showing which direction robot is facing
static void draw_direction_indicator(Position pos, Direction dir, int cell_size,
                                     int offset_x, int offset_y)
{
    // Calculate center of robot's cell
    int center_x = offset_x + pos.x * cell_size + cell_size / 2;
    int center_y = offset_y + pos.y * cell_size + cell_size / 2;
    int radius = cell_size / 3;

    // Start point is center
    int end_x = center_x;
    int end_y = center_y;

    // Calculate end point based on direction
    switch (dir)
    {
    case DIR_UP:
        end_y -= radius; // Line goes up
        break;
    case DIR_RIGHT:
        end_x += radius; // Line goes right
        break;
    case DIR_DOWN:
        end_y += radius; // Line goes down
        break;
    case DIR_LEFT:
        end_x -= radius; // Line goes left
        break;
    }

    setColour(red);
    setLineWidth(2);
    drawLine(center_x, center_y, end_x, end_y);
}

// Draw complete robot (body + direction indicator)
void robot_draw(Robot robot, DisplayConfig display)
{
    draw_robot_body(robot.pos, display.cell_size, display.offset_x, display.offset_y);
    draw_direction_indicator(robot.pos, robot.direction, display.cell_size,
                             display.offset_x, display.offset_y);
}

// MOVEMENT LOGIC BELOW and RENDERING UPDATES

/**
 * Redraw the foreground layer with current state
 * Called after each robot action to update display
 */
static void redraw_scene(Arena arena, Robot robot, DisplayConfig display)
{
    foreground(); // Select foreground layer
    clear();

    // Draw markers and robot
    arena_draw_foreground(arena, display);
    robot_draw(robot, display);
}

static void final_scene(Arena arena, Robot robot, DisplayConfig display)
{
    foreground(); // Select foreground layer
    clear();

    robot_draw(robot, display);
    sleep(400); // pause to show robot at final position
    arena_draw_foreground(arena, display);
}

/**
 * Idea:
 *  Mark current cell as visited
 *  Pick up marker if exists
 *  Try all 4 directions:
 *    - Turn to face direction
 *    - If can move and haven't visited: false, move, recurse, backtrack
 *  Return true if all presents collected to stop any backtrack movement
 *
 * visited - 2D array tracking which cells have been explored
 */
static bool explore_dfs(Robot *robot, Arena *arena, int visited[][MAX_GRID_SIZE],
                        DisplayConfig display)
{
    // Mark current cell as visited
    visited[robot->pos.y][robot->pos.x] = 1;

    // Pick up marker if exists
    if (atMarker(robot, arena))
    {
        pickUpMarker(robot, arena);
        redraw_scene(*arena, *robot, display);
        sleep(200);

        // DELETE BELOW IF YOU WANT ROBOT TO EXPLORE WHOLE GRID NO MATTER WHAT !!!!! Poor Electrical Thing if it was deleted
        if (robot->picked_markers == arena->number_of_presents)
        {
            return true; // all markers collected
        }
    }

    // Try all four directions
    for (int dir = 0; dir < 4; dir++)
    {
        while (robot->direction != dir)
        {
            right(robot);
            redraw_scene(*arena, *robot, display);
            sleep(150);
        }

        // Check if can move forward and haven't visited next cell
        if (canMoveForward(robot, arena))
        {
            Position next = robot_get_next_position(robot);

            if (!visited[next.y][next.x])
            {
                // Save current position for backtracking
                Position prev = robot->pos;

                // Move forward
                forward(robot, arena);
                redraw_scene(*arena, *robot, display);
                sleep(50);

                // Recursively explore from new position
                if (explore_dfs(robot, arena, visited, display))
                {
                    return true; // propagate completion up the stack
                }

                robot->pos = prev;
                redraw_scene(*arena, *robot, display);
                sleep(100);
            }
        }
    }

    return false; // didn't find all presents yet
}

// Entry point for exploration algorithm
void robot_explore_all(Robot *robot, Arena *arena, DisplayConfig display)
{
    int visited[MAX_GRID_SIZE][MAX_GRID_SIZE] = {0};

    // Explore entire arena
    explore_dfs(robot, arena, visited, display);
    sleep(500); // pause before dropping markers
    dropMarker(robot, arena);
    final_scene(*arena, *robot, display);
}
