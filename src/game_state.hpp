#pragma once

#include <SFML/Graphics.hpp>
#include "field.hpp"
#include "creatures.hpp"

class Field;

enum State {
  kInProcess,
  kVictory,
  kDefeat
};

class Observer {
public:
  State state = kInProcess;
  int cookie_count = 0;
  int life_count = 3;
  int score = 0;
  void CheckCookie(Field &, sf::FloatRect);
  void CheckGhost(sf::FloatRect, sf::FloatRect, sf::FloatRect, sf::FloatRect);
  static void IfEnter(sf::RenderWindow&, Pacman&, std::vector<Ghost>&, Observer&, Field&, Paths&);
};