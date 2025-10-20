## Logic

- Gather all necessary arguments to initialize the screen and grid.
- Randomly place obstacles and presents across the grid, using a different approach for circular paths.
- Position the robot on an unoccupied cell facing upward.
- Navigate the grid, checking each cell and collecting all presents.
- Move the robot to a corner to drop the presents after completing the collection.
- Display a win message.


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
# Small 30x30 arena with 5 obstacles and 3 presents
./program 30 30 5 3 0 | java -jar drawapp-4.5.jar

```

**Circular arena:**
```bash
# 30x30 circular arena with 4 presents in center
./program 30 30 0 4 1 | java -jar drawapp-4.5.jar

```

### Parameters
- **width**: Width of the arena (1-50)
- **height**: Height of the arena (1-50)
- **num_obstacles**: Number of random obstacles (ignored if is_circular=1)
- **num_presents**: Number of markers/presents for the robot to collect
- **is_circular**: 0 for rectangular arena, 1 for circular arena with ring of obstacles
