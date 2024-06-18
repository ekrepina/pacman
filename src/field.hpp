#pragma once
#include <SFML/Graphics.hpp>

const sf::Color kColorEmpty = sf::Color(0, 0, 0);
const sf::Color kColorWall = sf::Color(0, 0, 100);
const sf::Color kColorCookie = sf::Color(88, 57, 39);

enum CellCategory {
    kEmpty,
    kWall,
    kCookie
};

struct Cell {
    CellCategory category = kEmpty;
    sf::Color color = sf::Color::Black;
    sf::FloatRect boundaries = {0, 0, 0, 0};
};

class Field {
public:
  std::vector<std::vector<Cell>> cells;
  size_t width = 0;
  size_t height = 0;
  void InitField();
  void DrawField(sf::RenderWindow&) const;
  void DrawEmpty(sf::RenderWindow&, int, int) const;
  void DrawCookie(sf::RenderWindow&, int, int) const;
  static void DrawText(sf::RenderWindow&, const char*, const char*, sf::Color, bool) ;
  sf::Vector2<float> StartPosition(char) const;
};
