## My Comments

- I decided to use OOP-kinda concept as it is more familiar way of doing games ( from PyGame )
- DFS alg was used ( https://www.geeksforgeeks.org/dsa/depth-first-search-or-dfs-for-a-graph/ AND https://youtu.be/W9F8fDQj7Ok?si=msEleWT-d0M458S8)
- More about classes : https://www.pvv.ntnu.no/~hakonhal/main.cgi/c/classes/

- In my logic robot doesn't know about the number of presents, hence it should go through all the cells, however, I do not want to be marked down, so I added the function
that stops the robot once it collected all the presenets ( please, delete it, if u want to see poor electircal thing explore the grid for no reason !!! )
- some functions in the robot class are not used to control it ( or at least I believe so ), they either act as a helper function ( eg draw smth ) or like a second or third brain in operations managment to simplify main file

## Logic

- Gather all necessary arguments to initialize the screen and grid.
- Randomly place obstacles and presents across the grid, using a different approach for circular paths.
- Position the robot on an unoccupied cell facing upward.
- Navigate the grid, checking each cell and collecting all presents.
- After checking ALL the cells, it waits a bit, and then drops presents

## Compilation and Running
### Compilation
```bash
gcc -o program main.c arena.c robot.c graphics.c -I.
```

### Running with Command Line Arguments
```bash
./program <width> <height> <num_obstacles> <num_presents> <is_circular> | java -jar drawapp-4.5.jar

```

### Examples
**Rectangular arena:**
```bash
# Small 10x10 arena with 5 obstacles and 3 presents
./program 10 10 5 3 0 | java -jar drawapp-4.5.jar

```

**Circular arena:**
```bash
# 30x30 circular arena with 4 presents in center
./program 10 10 0 4 1 | java -jar drawapp-4.5.jar

```

### Parameters
- **width**: Width of the arena (1-50)
- **height**: Height of the arena (1-50)
- **num_obstacles**: Number of random obstacles (ignored if is_circular=1)
- **num_presents**: Number of markers/presents for the robot to collect
- **is_circular**: 0 for rectangular arena, 1 for circular arena with ring of obstacles
