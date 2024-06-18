#pragma once
#include <SFML/Graphics.hpp>
#include "field.hpp"
#include "paths.hpp"

class Field;
class Paths;

enum Direction {
  kUp,
  kRight,
  kDown,
  kLeft,
  kNone
};

class Creature {
public:
  bool is_stopped = true;
  virtual void InitCreature(Field&, Paths&, int) = 0;
  virtual void ChangeDirection(int) = 0;
  virtual void UpdateCreature(float elapsedTime, Field &field, int) = 0;
  static bool CheckWallsCollision(Field&, const sf::FloatRect&, sf::Vector2f&);
};

class Pacman : public Creature {
public:
  Direction direction = kNone;
  int im_state = 0;
  int time_im = 0;
  sf::CircleShape shape;
  void InitCreature(Field&, Paths&, int) override;
  void ChangeDirection(int) override;
  void UpdateCreature(float elapsedTime, Field &field, int) override;
};

class Ghost : public Creature {
public:
  Direction direction = kDown;
  sf::RectangleShape shape;
  sf::Color color;
  int im_state = 0;
  int time_im = 0;
  void InitCreature(Field&, Paths&, int) override;
  void ChangeDirection(int) override;
  void UpdateCreature(float elapsedTime, Field &field, int) override;
};
