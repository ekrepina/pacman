#include "field.hpp"

constexpr int kCellSize = 30;
constexpr int kFieldSize = 21;

constexpr char kMaze[] = "WWWWWWWWWWWWWWWWWWWWW"
                         "WCCCWCCCCCCCCCCCWCCCW"
                         "WCWCCCWWWWCWWWWCCCWCW"
                         "WCWWWCCCCCCCCCCCWWWCW"
                         "WCCCCCWCWWWWWCWCCCCCW"
                         "WCWWCWWCGEGEGCWWCWWCW"
                         "WCCCCCWCWCWCWCWCCCCCW"
                         "WCWWWCCCWCWCWCCCWWWCW"
                         "WCCCCCWWWCWCWWWCCCCCW"
                         "WWWCWCCCCCCCCCCCWCWWW"
                         "EEECWCWWCWWWCWWCWCEEE"
                         "WWWCWCWWCCCCCWWCWCWWW"
                         "WCCCCCCCCWWWCCCCCCCCW"
                         "WCWWWCWWCCPCCWWCWWWCW"
                         "WCCWCCCWCWWWCWCCCWCCW"
                         "WWCCCWCCCCWCCCCWCCCWW"
                         "WWCWWWCWWCCCWWCWWWCWW"
                         "WCCCCCCWCCWCCWCCCCCCW"
                         "WCWWCWWWCWWWCWWWCWWCW"
                         "WCCCCCCCCCCCCCCCCCCCW"
                         "WWWWWWWWWWWWWWWWWWWWW";

const char kMarkerWall = 'W';
const char kMarkerEmpty = 'E';
const char kMarkerCookie = 'C';
const char kMarkerPacman = 'P';

sf::Vector2<float> Field::StartPosition(char marker) const {
  for (int x = 0; x < kFieldSize; ++x) {
    for (int y = 0; y < kFieldSize; ++y) {
      if (kMaze[y * width + x] == marker) {
        return {static_cast<float>(x * kCellSize), static_cast<float>(y * kCellSize)};
      }
    }
  }
  return {};
}

void Field::InitField() {
  width = kFieldSize;
  height = kFieldSize;
  cells = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
  for (int x = 0; x < height; ++x) {
    for (int y = 0; y < width; ++y) {
      cells[x][y].boundaries.left = static_cast<float>(y) * kCellSize;
      cells[x][y].boundaries.top = static_cast<float>(x) * kCellSize;
      cells[x][y].boundaries.width = kCellSize;
      cells[x][y].boundaries.height = kCellSize;
      switch (kMaze[x * width + y]) {
        case kMarkerWall:
          cells[x][y].category = CellCategory::kWall;
          cells[x][y].color = kColorWall;
          break;
        case kMarkerEmpty:
          cells[x][y].category = CellCategory::kEmpty;
          cells[x][y].color = kColorEmpty;
          break;
        case kMarkerCookie:
          cells[x][y].category = CellCategory::kCookie;
          cells[x][y].color = kColorEmpty;
          break;
        default:
          cells[x][y].category = CellCategory::kEmpty;
          cells[x][y].color = kColorEmpty;
      }
    }
  }
}

void Field::DrawField(sf::RenderWindow& window) const {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      sf::RectangleShape cell;
      DrawEmpty(window, i, j);
      if (cells[i][j].category == kCookie) {
        DrawCookie(window, i, j);
      }
    }
  }
}

void Field::DrawEmpty(sf::RenderWindow &window, int i, int j) const {
  sf::RectangleShape cell;
  cell.setFillColor(cells[i][j].color);
  cell.setSize({kCellSize, kCellSize});
  cell.setPosition({cells[i][j].boundaries.left, cells[i][j].boundaries.top});
  window.draw(cell);
}

void Field::DrawCookie(sf::RenderWindow &window, int i, int j) const {
  sf::CircleShape cookie = sf::CircleShape(15);
  cookie.setPosition({cells[i][j].boundaries.left, cells[i][j].boundaries.top});
  cookie.setFillColor(kColorCookie);
  cookie.setOutlineColor(kColorEmpty);
  cookie.setOutlineThickness(-12);
  window.draw(cookie);
}

void Field::DrawText(sf::RenderWindow &window, const char* str1, const char* str2, sf::Color color, bool res) {
  float coord = 0;
  if (res) {
    coord = 140;
  } else {
    coord = 115;
  }
  sf::Font font;
  font.loadFromFile("../assets/font.ttf");
  sf::Text text;
  text.setString(str1);
  text.setCharacterSize(50);
  text.setFillColor(color);
  text.setFont(font);
  text.setOutlineThickness(5);
  text.setPosition(coord, 150);
  window.draw(text);
  text.setString(str2);
  text.setCharacterSize(20);
  text.setFillColor(color);
  text.setFont(font);
  text.setOutlineThickness(5);
  text.setPosition(98, 302);
  window.draw(text);
}
