# Caterpillar

A Snake-style game, built incrementally while learning C++ and SDL2.

## Current Status

- **Terminal Snake** (`main.cpp`) — fully playable. Runs in the terminal using raw keyboard input for movement.
- **Visual Game Loop** (`basic_game_loop.cpp`) — in progress. An SDL2-based rendering loop with a movable rectangle, arrow-key input, and screen boundaries. This is the foundation for a graphical version of the game and will be progressively built out (grid-based movement, snake body, food, collision, timing) into a full visual version of Caterpillar.

## Build & Run

Requires SDL2 and CMake.

```bash
cmake -B build -S .
cmake --build build
```

Run the terminal version:
```bash
./build/snake
```

Run the visual game loop (in progress):
```bash
./build/basic_game_loop
```

## Roadmap

- [x] Terminal-based Snake with keyboard input
- [x] SDL2 window/renderer setup
- [x] Basic rectangle movement with arrow keys
- [ ] Frame timing (consistent movement speed)
- [ ] Boundary/wall collision
- [ ] Grid-based snake body (multiple segments)
- [ ] Food spawning and eating
- [ ] Full visual Snake game