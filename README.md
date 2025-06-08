# CTetris++

A feature-rich terminal-based Tetris game written in C++ with customizable visual styles and smooth gameplay.

## 🎮 Features

- **Terminal-based gameplay** with ANSI color support
- **Customizable tile styles** (light, clunky, clear, high)
- **Standard Tetris mechanics**:
  - 7 different tetromino pieces (I, L, J, T, S, Z, O)
  - Line clearing with scoring
  - Progressive difficulty levels
  - Proper rotation system
- **Real-time controls** with keyboard input
- **Score tracking** and level progression
- **Cross-platform** terminal support

## 🏗️ Project Structure

```
CTetris/
├── src/
│   ├── main.cpp           # Entry point and tile style definitions
│   ├── Tetris.h           # Main game class declaration
│   ├── Tetris.cpp         # Game logic implementation
│   ├── structures.h       # Data structures (Tile, Block, Tetromino)
│   └── CORE.h            # Terminal I/O utilities
├── scripts/
│   └── setup.sh          # Development setup script
├── build/
│   ├── obj/              # Object files (generated)
│   └── out               # Compiled executable (generated)
├── .gitignore            # Git ignore rules
├── makefile              # Build configuration
├── CONTRIBUTING.md       # Development guidelines
└── README.md            # This file
```

## 🚀 Quick Start

### Prerequisites

- C++ compiler with C++20 support (g++, clang++)
- Unix-like terminal (Linux, macOS, WSL)

### Building

```bash
# Clone the repository
git clone <repository-url>
cd CTetris

# Quick setup (recommended for first-time setup)
./scripts/setup.sh

# Or manual build
make

# Run with default settings
./build/out

# Run with custom board dimensions
./build/out <width> <height>
```

### Command Line Arguments

The game accepts optional width and height arguments to customize the board size:

```bash
./build/out [width] [height]
```

- **width**: Number of columns (default: 10)
- **height**: Number of rows (default: 24)

### Example Usage

```bash
# Default 10x24 board (standard Tetris size)
./build/out

# Wide board: 15 columns, 24 rows
./build/out 15 24

# Tall board: 10 columns, 30 rows  
./build/out 10 30

# Large board: 20 columns, 40 rows
./build/out 20 40

# Small board: 8 columns, 16 rows
./build/out 8 16
```

**Note**: Both arguments must be provided together - you cannot specify only width or only height.

## 🎯 Controls

| Key | Action |
|-----|--------|
| `a` | Move left |
| `d` | Move right |
| `s` | Move down (soft drop) |
| `k` | Rotate left |
| `l` | Rotate right |

## 🎨 Tile Styles

The game supports multiple visual styles for the tetromino blocks. You can modify these in `src/main.cpp`:

### Available Styles

1. **Light** - Clean 2x2 block style
   ```
   +------+
   |  @@  |
   |  @@  |
   +______+
   ```

2. **Clunky** - Bold bordered style
   ```
   #####
   # @ #
   #####
   ```

3. **Clear** - Minimalist style (default)

4. **High** - Decorative ASCII art style
   ```
    o-----o
   ( .---. )
   | |###| |
   ( '---' )
    o-----o
   ```

## 🔧 Customization

### Changing Tile Style

Edit `src/main.cpp` and modify the `Game` constructor call:

```cpp
// Use different tile style
Game tetris(light);  // or clunky, clear, high
```

### Game Settings

The `Game` constructor accepts these parameters:
- `Tile deafultTile` - Visual style for blocks
- `int width` - Board width (default: 10)
- `int height` - Board height (default: 24)
- `float inputDelay` - Input responsiveness (default: 20)
- `int borderWidth` - Border thickness (default: 2)
- `int borderHeight` - Border thickness (default: 2)

## 🏆 Scoring System

- **Single line**: 40 × (level + 1) points
- **Double line**: 100 × (level + 1) points
- **Triple line**: 300 × (level + 1) points
- **Tetris (4 lines)**: 1200 × (level + 1) points

## 🐛 Development

### Debug Controls

| Key | Action |
|-----|--------|
| `]` | Speed up game time |
| `[` | Slow down game time |

### Building from Source

The project uses a simple Makefile:

```bash
# Clean build
rm -rf build/out
make

# Manual compilation
g++ src/main.cpp -std=c++20 -o build/out
```

## 📋 System Requirements

- **OS**: Linux, macOS, or Windows with WSL
- **Compiler**: g++ with C++20 support
- **Terminal**: ANSI color support recommended
- **Dependencies**: Standard C++ library only

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is open source. Please check with the repository owner for specific licensing terms.

## 🚧 Future Enhancements

- [ ] High score persistence
- [ ] Multiplayer support
- [ ] Additional tile styles
- [ ] Sound effects
- [ ] Improved AI opponent
- [ ] Mobile terminal support

---

**Enjoy playing CTetris++!** 🎮

