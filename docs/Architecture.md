## Architecture

- _**class Creature**_ : 
  Pacman and ghosts have a common property – the inability to pass through walls, so for implementation it was decided to create the Creature class, from which the Pacman and Ghost classes are inherited. Some functions from Creature in the heirs will be overloaded, new ones will be added (since the player needs to control the Pacman and its movement differs from the movement of  ghosts). 

- _**class Field**_ :
  There is a Field class that stores the playing field itself in the form of a two-dimensional vector of Cell cells, each of which has one of three types: empty, with a dot and a wall. This is necessary for correct rendering of the field and determining the possible movement of Pacman and ghosts

- _**class Observer**_ :
  To track the current status of the game and complete it with victory or defeat, an Observer class has been created that counts the number of Pacman lives, points eaten, score and changes the state of the game.



<!--- ###################################################################### -->

## Patterns

- Factory
- Observer
