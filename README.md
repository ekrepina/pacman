# Project Pac-Man

<!--- ###################################################################### -->

## Description

There is a maze map, the corridors of which are filled with dots. The player controls Pac-Man,
who walks through a maze and eats dots. There are also ghosts in the maze that
chasing the hero, when colliding with them Pac-Man loses his life or dies,
if lives are over.

<!--- ###################################################################### -->

## Interface

- [In Process](docs/Images/inprocess.png)
- [Victory](docs/Images/victory.png)
- [Defeat](docs/Images/defeat.png)

<!--- ###################################################################### -->

## Installation

C++ standard version - С++20

CMake minimum required version - 3.22

```
git clone git@github.com:ekrepina/pacman.git pacman
cd pacman
mkdir build
cd build
cmake PATH_TO_PROJECT
make
```

<!--- ###################################################################### -->

## Run

```
./bin/pacman
```

<!--- ###################################################################### -->

## Game controls
1) Arrows keys and WASD -- pacman movement
2) Enter -- restart in case of victory or defeat
3) Escape -- quit the game

<!--- ###################################################################### -->

## Useful links

- [Architectual decisions and design patterns](docs/Architecture.md)
- [UML diagram](docs/Images/UML.png)
- [Use case diagram](docs/Images/Use_case_diagram.png)
