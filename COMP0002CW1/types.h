// prevents multiple inclusions
#ifndef TYPES_H 
#define TYPES_H

#include <stdbool.h>


#define MAX_GRID_SIZE 50    // Maximum dimensions for the arena grid
#define GRID_FREE 0         // Cell value for free space
#define GRID_OBSTACLE 1     // Cell value for obstacles
#define GRID_MARKER 2       // Cell value for markers/presents to collect


typedef enum
{
    DIR_UP = 0,      // Robot facing upward (decreasing y)
    DIR_RIGHT = 1,   // Robot facing right (increasing x)
    DIR_DOWN = 2,    // Robot facing downward (increasing y)
    DIR_LEFT = 3     // Robot facing left (decreasing x)
} Direction;


typedef struct
{
    int x, y;  // array-based coordinates
} Position;


typedef struct
{
    int width, height;              // Dimensions of the arena
    int number_of_obstacles;        // Total obstacles placed (for rectangular mode)
    int number_of_presents;         // Total markers to collect
    bool is_circular;               // true: circular arena, false: rectangular arena
    int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];  // 2D grid storing cell values
} Arena;


typedef struct
{
    Position pos;          // Current position in the arena
    Direction direction;   // Current facing direction
    int picked_markers;    // Number of markers currently carried
} Robot;


typedef struct
{
    int cell_size;   // Size of each grid cell in pixels
    int offset_x;    // Horizontal offset from window edge
    int offset_y;    // Vertical offset from window edge
} DisplayConfig;




Arena arena_create(int width, int height, int num_obstacles, int num_presents, bool is_circular);
void arena_draw_background(Arena arena, DisplayConfig display);
void arena_draw_foreground(Arena arena, DisplayConfig display);
bool arena_is_valid_position(Position pos, Arena *arena);
int arena_get_cell(Position pos, Arena *arena);
void arena_set_cell(Position pos, int value, Arena *arena);
void forward(Robot *robot, Arena *arena);
void left(Robot *robot);
void right(Robot *robot);
int atMarker(Robot *robot, Arena *arena);
int canMoveForward(Robot *robot, Arena *arena);
void pickUpMarker(Robot *robot, Arena *arena);
void dropMarker(Robot *robot, Arena *arena);
int markerCount(Robot *robot);
Robot robot_create(Arena *arena);
void robot_draw(Robot robot, DisplayConfig display);
Position robot_get_next_position(Robot *robot);
void robot_explore_all(Robot *robot, Arena *arena, DisplayConfig display);

#endif