#include "game_state.hpp"
#include "field.hpp"
#include "creatures.hpp"

void Observer::CheckCookie(Field &field, sf::FloatRect bounds) {
  for (size_t i = 0; i < field.height; ++i) {
    for (size_t j = 0; j < field.width; ++j) {
      if (field.cells[i][j].category != CellCategory::kCookie) {
        continue;
      }
      sf::FloatRect cookie_bounds = {field.cells[i][j].boundaries.left + 10.f, field.cells[i][j].boundaries.top + 10.f,
                                     field.cells[i][j].boundaries.width - 20.f,
                                     field.cells[i][j].boundaries.height - 20.f};
      if (bounds.intersects(cookie_bounds)) {
        field.cells[i][j].category = kEmpty;
        ++cookie_count;
        ++score;
        if (cookie_count == 219) {
          state = kVictory;
          break;
        }
      }
    }
    if (state == kVictory) {
      break;
    }
  }
}

void Observer::CheckGhost(sf::FloatRect pacman, sf::FloatRect ghost1, sf::FloatRect ghost2,
                          sf::FloatRect ghost3) {
  if (pacman.intersects(ghost1) || pacman.intersects(ghost2) || pacman.intersects(ghost3)) {
    state = kDefeat;
  }
}


void Observer::IfEnter(sf::RenderWindow &window, Pacman &pacman, std::vector<Ghost>& ghosts, Observer &observer,
                           Field &field, Paths& paths) {
  observer.state = kInProcess;
  field.InitField();
  observer.life_count = 3;
  observer.cookie_count = 0;
  observer.score = 0;
  pacman.InitCreature(field, paths, 0);
  for (int i = 0; i < 3; ++i) {
    ghosts[i].InitCreature(field, paths, i);
  }
  pacman.direction = kNone;
  pacman.is_stopped = false;
  for (int i = 0; i < 3; ++i) {
    ghosts[i].is_stopped = false;
  }
  field.DrawField(window);
  window.draw(pacman.shape);
  for (int i = 0; i < 3; ++i) {
    window.draw(ghosts[i].shape);
  }
}

