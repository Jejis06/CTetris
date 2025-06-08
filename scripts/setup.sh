#!/bin/bash

# CTetris++ Setup Script
# This script helps set up the development environment

set -e

echo "🎮 CTetris++ Setup Script"
echo "========================="

# Check if g++ is installed
if ! command -v g++ &> /dev/null; then
    echo "❌ g++ compiler not found!"
    echo "Please install g++ with C++20 support:"
    
    # Detect OS and provide installation instructions
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "  Ubuntu/Debian: sudo apt-get install g++"
        echo "  CentOS/RHEL:   sudo yum install gcc-c++"
        echo "  Arch Linux:    sudo pacman -S gcc"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "  macOS: xcode-select --install"
        echo "  or install via Homebrew: brew install gcc"
    else
        echo "  Please install a C++20 compatible compiler"
    fi
    exit 1
fi

# Check C++20 support
echo "🔍 Checking C++20 support..."
cat > /tmp/cxx20_test.cpp << 'EOF'
#include <iostream>
#include <concepts>
template<typename T>
concept Printable = requires(T t) { std::cout << t; };
int main() { return 0; }
EOF

if g++ -std=c++20 /tmp/cxx20_test.cpp -o /tmp/cxx20_test 2>/dev/null; then
    echo "✅ C++20 support confirmed"
    rm -f /tmp/cxx20_test.cpp /tmp/cxx20_test
else
    echo "⚠️  C++20 support may be limited"
    echo "   The game should still compile, but you may need a newer compiler"
fi

# Create necessary directories
echo "📁 Creating build directories..."
mkdir -p build/obj

# Set up git hooks (if git repository exists)
if [ -d .git ]; then
    echo "🔧 Setting up git hooks..."
    mkdir -p .git/hooks
    
    # Pre-commit hook to run basic checks
    cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
echo "Running pre-commit checks..."
make clean > /dev/null 2>&1
if ! make > /dev/null 2>&1; then
    echo "❌ Build failed! Please fix compilation errors before committing."
    exit 1
fi
echo "✅ Build successful"
EOF
    
    chmod +x .git/hooks/pre-commit
    echo "✅ Git pre-commit hook installed"
fi

# Test build
echo "🔨 Testing build process..."
if make clean > /dev/null 2>&1 && make > /dev/null 2>&1; then
    echo "✅ Build test successful!"
    echo ""
    echo "🎉 Setup complete! You can now:"
    echo "   • Run 'make' to build the game"
    echo "   • Run 'make run' to build and play"
    echo "   • Run 'make help' to see all available commands"
    echo "   • Run './build/out' to play with default settings"
    echo "   • Run './build/out 15 30' for a 15x30 board"
else
    echo "❌ Build test failed. Please check for compilation errors."
    exit 1
fi 