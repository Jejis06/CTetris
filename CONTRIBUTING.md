# Contributing to CTetris++

Thank you for your interest in contributing to CTetris++! This document provides guidelines and information for contributors.

## 🚀 Quick Start for Contributors

1. **Fork the repository**
2. **Run the setup script**:
   ```bash
   ./scripts/setup.sh
   ```
3. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## 🏗️ Development Environment

### Prerequisites
- C++ compiler with C++20 support (g++, clang++)
- Unix-like terminal (Linux, macOS, WSL)
- Git for version control

### Setup
```bash
# Clone your fork
git clone https://github.com/your-username/CTetris.git
cd CTetris

# Run setup (checks dependencies, creates directories, sets up hooks)
./scripts/setup.sh

# Build and test
make clean && make
./build/out
```

## 📋 Code Style and Standards

### C++ Guidelines
- **C++20 Standard**: Use modern C++20 features where appropriate
- **Naming Conventions**:
  - Classes: `PascalCase` (e.g., `GameManager`)
  - Functions: `camelCase` (e.g., `processInput`)
  - Variables: `camelCase` (e.g., `currentScore`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_LEVEL`)
- **File Organization**:
  - Headers in `.h` files with corresponding `.cpp` implementation
  - Keep headers minimal and use forward declarations
  - Include guards or `#pragma once`

### Code Formatting
- **Indentation**: 4 spaces (no tabs)
- **Braces**: Opening brace on same line
- **Line Length**: Prefer lines under 100 characters
- **Comments**: Use `//` for single-line, `/* */` for multi-line

### Example Code Style
```cpp
class GameManager {
private:
    int currentLevel;
    bool isGameActive;

public:
    GameManager(int startLevel = 1) : currentLevel(startLevel), isGameActive(true) {
        // Constructor logic
    }
    
    void processInput(char input) {
        if (!isGameActive) {
            return;
        }
        
        switch (input) {
            case 'a':
                moveLeft();
                break;
            case 'd':
                moveRight();
                break;
            default:
                // Handle unknown input
                break;
        }
    }
};
```

## 🧪 Testing

### Manual Testing
- Test all control inputs (a, d, s, k, l)
- Test different board sizes
- Test line clearing mechanics
- Test game over conditions
- Test different tile styles

### Build Testing
```bash
# Clean build test
make clean && make

# Debug build test
make debug

# Run with different configurations
./build/out 8 20    # Small board
./build/out 15 30   # Large board
```

## 🐛 Debugging

### Debug Build
```bash
make debug
# Run with debugger
gdb ./build/out
```

### Common Issues
- **Compilation Errors**: Check C++20 compiler support
- **Terminal Issues**: Ensure ANSI color support
- **Input Problems**: Check terminal raw mode functionality

## 📝 Commit Guidelines

### Commit Message Format
```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

### Types
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (no logic changes)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

### Examples
```
feat(game): add pause functionality
fix(controls): resolve rotation bug in T-block
docs(readme): update build instructions
style(tetris): improve code formatting
```

## 🎯 Areas for Contribution

### High Priority
- [ ] **Bug Fixes**: Report and fix gameplay bugs
- [ ] **Performance**: Optimize game loop and rendering
- [ ] **Cross-platform**: Improve Windows/WSL compatibility

### Medium Priority
- [ ] **Features**: Add new tile styles or game modes
- [ ] **UI/UX**: Improve visual feedback and animations
- [ ] **Configuration**: Add config file support

### Low Priority
- [ ] **Sound**: Add sound effects
- [ ] **Multiplayer**: Network multiplayer support
- [ ] **AI**: Computer opponent

## 🔍 Code Review Process

1. **Self-Review**: Test your changes thoroughly
2. **Documentation**: Update relevant documentation
3. **Clean History**: Squash commits if necessary
4. **Pull Request**: Create PR with clear description
5. **Review**: Address feedback promptly

### Pull Request Template
```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Code refactoring

## Testing
- [ ] Tested on Linux
- [ ] Tested on macOS
- [ ] Tested different board sizes
- [ ] Tested all controls

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] No breaking changes
```

## 🤝 Getting Help

- **Issues**: Create GitHub issues for bugs or feature requests
- **Discussions**: Use GitHub discussions for questions
- **Code Questions**: Comment on specific lines in pull requests

## 📄 License

By contributing, you agree that your contributions will be licensed under the same license as the project.

---

Thank you for contributing to CTetris++! 🎮 