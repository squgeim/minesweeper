# minesweeper [![Build Status](https://travis-ci.com/squgeim/minesweeper.svg?branch=master)](https://travis-ci.com/squgeim/minesweeper)

A simple implementation of the classic Minesweeper in your terminal.

    ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
    │ │ │ │1│1│3│#│2│ │ │ │ │1│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │ │ │ │1│#│3│#│2│ │ │ │ │1│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │ │ │ │1│1│2│2│2│1│ │ │ │1│3│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │ │ │ │ │ │ │1│#│1│ │ │ │ │2│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │ │ │1│2│2│1│1│1│1│ │ │ │ │1│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │1│1│1│#│#│1│ │ │ │ │ │ │ │1│1│1│1│2│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│1│ │ │ │ │1│1│1│ │ │ │ │2│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│1│ │ │ │ │1│#│1│ │ │ │ │3│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│3│1│2│1│1│1│1│1│ │1│1│2│3│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│1│ │1│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│3│1│2│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
    │▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│▒│
    └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘

### Motivation

Just wanted a simple project to practice C.

## How to Play

- `←` `↑` `↓` `→` to move the cursor around.
- `SPACE` to flag a cell. Flagged cells are represented with a `#`.
- `ENTER` to reveal a cell. Bomb cells are represented with a `◆`.
- `q` to exit at any time.

## Architecture

You should find the code self-explanatory.

`window.c` manages the view layer of the game. It decides how the game is
printed and how user input is taken. We use `ncurses` to print the game and take
user input.

`libminesweeper` manages the game state and game logic.

## Build

Use `make` to build the project.

```sh
$ make build
```

You may sometimes need to clean previous build artifacts:

```sh
$ make clean
```

For a debug-ready build:

```sh
$ make debug
```

> I need help improving the Makefile. Any contributions welcome.

I am developing the project on MacOS with the default build chain installed by
XCode. That means even though I say `gcc` in the Makefile, I am actually building
with `Clang`. They aim to be source compatible with the original `gcc`.

My current "gcc" version = `4.2.1`

```sh
$ gcc --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/usr/include/c++/4.2.1
Apple LLVM version 10.0.1 (clang-1001.0.46.4)
Target: x86_64-apple-darwin18.6.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```
