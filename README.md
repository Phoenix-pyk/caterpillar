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
- [x] Frame timing (consistent movement speed)
- [x] Boundary/wall collision
- [x] Game-over state
- [x] Grid-based snake body (multiple segments)
- [x] Food spawning and eating
- [ ] Full visual Snake game
- [ ] Game-over screen + replay option


## Setup

### Dependencies

This project uses SDL2 for rendering.

**macOS (Homebrew):**
```bash
brew install sdl2-compat
```

> **Note:** On Apple Silicon Macs, Homebrew may install `sdl2-compat` instead of the plain `sdl2` formula. If `find_package(SDL2 REQUIRED)` fails in CMake with `SDL.h file not found`, check which path Homebrew actually used:
> ```bash
> brew --prefix sdl2
> ```
> Then confirm `CMakeLists.txt` has `CMAKE_PREFIX_PATH` pointing at that exact path — it may be `/opt/homebrew/opt/sdl2-compat` rather than `/opt/homebrew/opt/sdl2`.

### Building & Running (CLion)

- Make sure the Run/Debug Configuration dropdown (top right) is set to the **CMake target** (e.g. `basic_game_loop`), not a plain `.cpp` file — single-file mode bypasses `CMakeLists.txt` entirely and will fail to find SDL headers.
- If reports **"Not a plain CMake project"** under Settings → Build, Execution, Deployment → CMake, the project's `.idea` link is broken. Fix:
```bash
  rm -rf .idea
```
Then reopen the project folder with (File → Open) and let it reconfigure CMake from scratch.