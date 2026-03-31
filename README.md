The Pale Below

A 2D Metroidvania built in C++ with SFML.

⚠️ **Early Development** – Core mechanics are implemented but the game currently has only test-textures and no story. What you see is a work in progress.

---

## About

The Pale Below is a 2D Metroidvania currently in solo development. The fundamental gameplay mechanics are in place – movement, exploration, and the core game loop – but art assets and narrative are not yet part of the project.

---

## Windows

Download and run [install.exe](installer) file in the installer folder.

## macOS & Linux

## Requirements

- A C++ compiler with C++17 support (e.g. **g++**)
- **SFML 2.x**

### Installing SFML

**Ubuntu / Debian**
```bash
sudo apt install libsfml-dev
```

**macOS (Homebrew)**
```bash
brew install sfml
```

---

## Building

Clone the repository and run the following command from the project root:

```bash
g++ src/main.cpp src/GameLogic.cpp src/DemoLevel.cpp -o build/game -lsfml-graphics -lsfml-window -lsfml-system
```

Then run the game:

```bash
# Linux / macOS
./build/game
```

> Make sure the `build/` directory exists before compiling, or create it first with `mkdir build`. Also delete the .exe file.

---

## Project Status

- [x] Core movement & physics
- [x] Basic game loop
- [x] Test-Textures & art assets
- [ ] Story & world design
- [ ] Audio

---

## License

MIT License – see [LICENSE](LICENSE) for details.
