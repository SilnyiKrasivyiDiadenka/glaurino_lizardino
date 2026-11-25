# glaurino_lizardino

**A modernized C++ port of the classic Glaurung chess engine by Tord Romstad.**

Glaurung is the direct predecessor of [official-stockfish/Stockfish](https://github.com/official-stockfish/Stockfish). This repository contains a cleaned-up, modernized version of Glaurung 2.2 (based on the original sources from [phenri/glaurung](https://github.com/phenri/glaurung) and the initial Stockfish import of Glaurung 2.1).

## Project Goals

The aim is not to change playing strength or features, but to modernize the codebase so it is cleaner, more maintainable, and easier to compile with contemporary toolchains. Functional behavior should remain identical (or as close as possible). The modernization also serves as a form of code preservation: making the engine straightforward to build on any future platform or operating system, while keeping the logic easier to read, analyze, and understand.

1. **Modernize C++**

   Replace raw C-style arrays with `std::vector` and `std::array` (and other standard containers where appropriate).

2. **Abstract interfaces & orchestrators**

   Hide complex functionality behind abstract interfaces (pure virtual classes) and orchestrator classes. This improves modularity without changing external behavior.

3. **Remove platform-dependent code**

   Replace all platform-specific code (locks, threads, console handling, etc.) with standard modern C++ facilities (`std::mutex`, `std::thread`, standard I/O, etc.).

4. **CMake build system**

   Replace the original Makefiles with a `CMakeLists.txt` so the engine builds cleanly on any platform that has CMake.

5. **No functional changes**

   Same engine, same strength, same style. The goal is a cleaner implementation that modern compilers can optimize better, hopefully yielding a small performance improvement as a side effect.

6. **Standard C++26**

   The code targets standard C++26 only. It should compile on any platform with a modern C++ compiler and CMake (or can be adapted easily).

## Origin

- Original author: **Tord Romstad**
- Glaurung 2.1 was the base that Marco Costalba forked to create Stockfish (first commit in the Stockfish repository is the import of Glaurung 2.1).
- Glaurung 2.2 is the last version by Tord before the Stockfish era.
- Sources used:
  - [official-stockfish/Stockfish](https://github.com/official-stockfish/Stockfish) (initial commit = Glaurung 2.1)
  - [phenri/glaurung](https://github.com/phenri/glaurung) (Glaurung 2.2)

## License

GPL-3.0 (same as the original Glaurung and Stockfish repositories).

See [LICENSE](LICENSE) for the full license text.

## Building

```bash
git clone https://github.com/SilnyiKrasivyiDiadenka/glaurino_lizardino.git
cd glaurino_lizardino
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
