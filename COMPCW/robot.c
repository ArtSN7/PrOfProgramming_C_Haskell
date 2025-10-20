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

//Create robot at random free position
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

// Turns below
void left(Robot *robot)
{
    robot->direction = (robot->direction + 3) % 4;
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
    clear();      // Clear previous frame

    // Draw current state: markers and robot
    arena_draw_foreground(arena, display);
    robot_draw(robot, display);
}

/**
 * Depth-First Search exploration algorithm
 * Systematically visits all reachable cells, collecting markers
 *
 * Algorithm:
 * 1. Mark current cell as visited
 * 2. Pick up marker if present
 * 3. Try all 4 directions:
 *    - Turn to face direction
 *    - If can move and haven't visited: move, recurse, backtrack
 * 4. Return (backtrack happens automatically via recursion)
 *
 * @param visited 2D array tracking which cells have been explored
 */
static void explore_dfs(Robot *robot, Arena *arena, int visited[][MAX_GRID_SIZE],
                        DisplayConfig display)
{
    // Mark current cell as visited
    visited[robot->pos.y][robot->pos.x] = 1;

    // Pick up marker if present
    if (atMarker(robot, arena))
    {
        pickUpMarker(robot, arena);
        redraw_scene(*arena, *robot, display);
        sleep(200); // Pause to show marker collection
    }

    // Try all four directions (up, right, down, left)
    for (int dir = 0; dir < 4; dir++)
    {
        // Turn robot to face current direction
        while (robot->direction != dir)
        {
            right(robot); // Keep turning right until facing desired direction
            redraw_scene(*arena, *robot, display);
            sleep(50); // Pause to show rotation
        }

        // Calculate where robot would move
        Position next = robot_get_next_position(robot);

        // If can move and haven't visited that cell
        if (arena_is_valid_position(next, arena) && !visited[next.y][next.x])
        {
            // Move forward
            forward(robot, arena);
            redraw_scene(*arena, *robot, display);
            sleep(50);

            // Recursively explore from new position
            explore_dfs(robot, arena, visited, display);

            // Backtrack: turn around and return to previous cell
            right(robot);
            right(robot); // 180 degree turn
            redraw_scene(*arena, *robot, display);
            sleep(50);

            // Move back to previous cell
            next = robot_get_next_position(robot);
            if (arena_is_valid_position(next, arena))
            {
                forward(robot, arena);
                redraw_scene(*arena, *robot, display);
                sleep(50);
            }
        }
    }
    // Function returns, completing backtrack
}

/**
 * Entry point for exploration algorithm
 * Initializes visited array and starts DFS
 */
void robot_explore_all(Robot *robot, Arena *arena, DisplayConfig display)
{
    // Initialize visited array (all cells marked as unvisited)
    int visited[MAX_GRID_SIZE][MAX_GRID_SIZE] = {0};

    // Start depth-first search from robot's current position
    explore_dfs(robot, arena, visited, display);
}
