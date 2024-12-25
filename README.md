# so\_long

A small 2D game project.

The goal of this project is to create a simple game where a player can navigate through a maze, collect items, avoid enemies (optional), and reach the exit to win.
The project focuses on understanding graphical programming, event handling, and memory management in C.

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Game Design](#game-design)
7. [Resources](#resources)
8. [Credits](#credits)

---

## Overview

**so_long** uses the **MiniLibX** library.

---

## Features

- **Basic Gameplay**: Navigate a character through a map to collect items and reach the exit.
- **Tile-Based Rendering**: Display the map using sprites for walls, collectibles, the player, and the exit.
- **Event Handling**: Use keyboard inputs to move the character.
- **Custom Map Loading**: Support for user-defined maps with `.ber` file extension.
- **Win Condition**: Collect all items and reach the exit.
- **Error Management**: Handle invalid maps.

---

## Requirements

### System

- Unix-based operating system (Linux or macOS).
- C compiler.

### Libraries

- Standard C libraries.
- xorg, x11 and zlib
```bash
sudo apt update && sudo apt install xorg libxext-dev zlib1g-dev libbsd-dev
```

---

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Zak4b/so_long.git
   cd so_long
   ```

2. Compile the project:

   ```bash
   make
   ```

3. Run the game with a map file:

   ```bash
   ./so_long maps/default.ber
   ```

---

## Usage

### Controls

- **WASD**: Move the character up, down, left, or right.
- **ESC**: Exit the game.

### Map Requirements

The game requires a valid `.ber` map file.
The map must adhere to the following rules:

1. The map must be rectangular.
2. The map must be surrounded by walls (`1`).
3. The map must contain:
   - At least one collectible (`C`).
   - One player spawn point (`P`).
   - One exit (`E`).
4. The map can contain monsters (`M`).
5. Any other characters will be considered invalid.

Example of a valid map:

```
111111
1P0C01
100001
1C0E11
111111
```

---

## Game Design

### Sprites

- **Walls (`1`)**: Represented as impassable tiles.
- **Player (`P`)**: Controlled by the user.
- **Monster (`M`)**: Controlled by the user.
- **Collectibles (`C`)**: Items to gather before reaching the exit.
- **Exit (`E`)**: Becomes accessible once all collectibles are gathered.

---

## Resources

- [**MiniLibX Documentation**](https://harm-smits.github.io/42docs/libs/minilibx)

---

## Credits

[Player and monster's sprites](https://game-endeavor.itch.io/mystic-woods)
Developed by: asene\
Part of the 42 curriculum.

---

