#include "creatures.hpp"
#include "field.hpp"
#include <cmath>
#include <limits>

static constexpr float kEpsilon = std::numeric_limits<float>::epsilon();

constexpr float kRadiusPacman = 15;
constexpr float kSideGhost = 30;

std::map<Direction, int> kImageGhost{{kNone,  60},
                                     {kDown,  60},
                                     {kUp,    0},
                                     {kLeft,  120},
                                     {kRight, 180}};

std::map<Direction, std::pair<int, int>> kImagePacman{{{kNone, std::make_pair(0, 58)},
                                                       {kDown, std::make_pair(90, 0)},
                                                       {kUp, std::make_pair(60, 0)},
                                                       {kLeft, std::make_pair(0, 0)},
                                                       {kRight, std::make_pair(30, 0)}}};


constexpr float kSpeedPacman = 100;
constexpr float kSpeedGhost = 90;

constexpr char kMarkerPacman = 'P';
constexpr char kMarkerGhost = 'G';

sf::Rect<int> kPacmanRect = {58, 0, 30, 30};
std::vector<sf::Rect<int>> kGhostRect = {{60, 0, 30, 30},
                                           {60, 30, 30, 30},
                                           {60, 60, 30, 30}};


void Pacman::InitCreature(Field &field, Paths& paths, int ind) {
  is_stopped = false;
  shape.setRadius(kRadiusPacman);
  shape.setTexture(&paths.pacman_texture);
  shape.setTextureRect(kPacmanRect);
  shape.setPosition(field.StartPosition(kMarkerPacman));
}

void Pacman::ChangeDirection(int) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    direction = Direction::kUp;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    direction = Direction::kRight;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    direction = Direction::kDown;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    direction = Direction::kLeft;
  }
  shape.setTextureRect({kImagePacman[direction].second + 29 * im_state, kImagePacman[direction].first, 30, 30});
  ++time_im;
  if (time_im == 3) {
    im_state = 1 - im_state;
    time_im = 0;
  }
  if (direction == Direction::kNone) {
    im_state = 0;
  }
}

void Pacman::UpdateCreature(float elapsedTime, Field &field, int ind) {
  if (is_stopped) {
    return;
  }
  sf::FloatRect bounds = shape.getGlobalBounds();
  if (bounds.left <= -30.f) {
    shape.move(22 * 30.f, 0);
  }
  if (bounds.left >= 21 * 30.f) {
    shape.move(-22 * 30.f, 0);
  }
  const float step = kSpeedPacman * elapsedTime;
  ChangeDirection(0);
  sf::Vector2f offset(0.f, 0.f);
  switch (direction) {
    case Direction::kUp:
      offset.y -= step;
      break;
    case Direction::kDown:
      offset.y += step;
      break;
    case Direction::kLeft:
      offset.x -= step;
      break;
    case Direction::kRight:
      offset.x += step;
      break;
    case Direction::kNone:
      break;
  }
  if (CheckWallsCollision(field, bounds, offset)) {
    direction = Direction::kNone;
  }
  shape.move(offset);
}

Direction ShiftDirection(float left_shift, float right_shift, float up_shift, float down_shift, float min_shift) {
  Direction result = Direction::kNone;
  if ((left_shift >= min_shift) && (left_shift <= 15.0)) {
    result = Direction::kLeft;
  } else if ((right_shift >= min_shift) && (right_shift <= 15.0)) {
    result = Direction::kRight;
  } else if ((up_shift >= min_shift) && (up_shift <= 15.0)) {
    result = Direction::kUp;
  } else if ((down_shift >= min_shift) && (down_shift <= 15.0)) {
    result = Direction::kDown;
  }
  return result;
}

bool Creature::CheckWallsCollision(Field &field, const sf::FloatRect &bounds, sf::Vector2f &offset) {
  sf::FloatRect new_bounds = {bounds.left + offset.x, bounds.top + offset.y, bounds.width, bounds.height};
  bool collision = false;
  for (size_t i = 0; i < field.height; ++i) {
    for (size_t j = 0; j < field.width; ++j) {
      if (field.cells[i][j].category != CellCategory::kWall) {
        continue;
      }
      if (new_bounds.intersects(field.cells[i][j].boundaries)) {
        float down_shift =
                field.cells[i][j].boundaries.top + field.cells[i][j].boundaries.height - new_bounds.top;
        float up_shift = new_bounds.top + new_bounds.height - field.cells[i][j].boundaries.top;
        float right_shift =
                field.cells[i][j].boundaries.left + field.cells[i][j].boundaries.width - new_bounds.left;
        float left_shift = new_bounds.left + new_bounds.width - field.cells[i][j].boundaries.left;
        float shift = std::max(std::abs(offset.x), std::abs(offset.y));

        Direction shift_direction = ShiftDirection(left_shift, right_shift, up_shift, down_shift, shift + kEpsilon);
        if (shift_direction == Direction::kNone) {
          shift_direction = ShiftDirection(left_shift, right_shift, up_shift, down_shift, 0);
        }
        switch (shift_direction) {
          case Direction::kUp:
            offset.y -= up_shift;
            break;
          case Direction::kDown:
            offset.y += down_shift;
            break;
          case Direction::kLeft:
            offset.x -= left_shift;
            break;
          case Direction::kRight:
            offset.x += right_shift;
            break;
          case Direction::kNone:
            break;
        }
        collision = true;
        new_bounds = {bounds.left + offset.x, bounds.top + offset.y, bounds.width, bounds.height};
      }
    }
  }
  return collision;
}

void Ghost::InitCreature(Field& field, Paths& paths, int ind) {
  is_stopped = false;
  shape.setSize({kSideGhost, kSideGhost});
  shape.setTexture(&paths.ghosts_texture);
  shape.setTextureRect(kGhostRect[ind]);
  sf::Vector2<float> start_position = field.StartPosition(kMarkerGhost);
  start_position.x += static_cast<float>(ind * 60);
  shape.setPosition(start_position);
}

void Ghost::ChangeDirection(int ind) {
  direction = Direction(rand() % 4);
}

void Ghost::UpdateCreature(float elapsedTime, Field &field, int ind) {
  if (is_stopped) {
    return;
  }
  if (direction == kNone) {
    ChangeDirection(ind);
  }
  sf::FloatRect bounds = shape.getGlobalBounds();
  if (bounds.left <= -30.f) {
    shape.move(22 * 30.f, 0);
  }
  if (bounds.left >= 21 * 30.f) {
    shape.move(-22 * 30.f, 0);
  }
  const float step = kSpeedGhost * elapsedTime;
  sf::Vector2f offset(0.f, 0.f);
  switch (direction) {
    case Direction::kUp:
      offset.y -= step;
      break;
    case Direction::kDown:
      offset.y += step;
      break;
    case Direction::kLeft:
      offset.x -= step;
      break;
    case Direction::kRight:
      offset.x += step;
      break;
    case Direction::kNone:
      break;
  }
  if (CheckWallsCollision(field, bounds, offset)) {
    ChangeDirection(ind);
  }
  shape.setTextureRect({kImageGhost[direction] + im_state * 30, ind * 30, 30, 30});
  ++time_im;
  if (time_im == 3) {
    im_state = 1 - im_state;
    time_im = 0;
  }
  shape.move(offset);
}
