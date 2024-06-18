#include "field.hpp"
#include "creatures.hpp"
#include "game_state.hpp"
#include <SFML/Graphics.hpp>

void handleEvents(sf::RenderWindow &window) {
  sf::Event event{};
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      window.close();
    }
  }
}


void update(sf::Clock &clock, Pacman &pacman, std::vector<Ghost> &ghosts, Observer &observer, Field &field) {
  const float elapsed_time = clock.getElapsedTime().asSeconds();
  clock.restart();
  pacman.UpdateCreature(elapsed_time, field, 0);
  for (int i = 0; i < 3; ++i) {
    ghosts[i].UpdateCreature(elapsed_time, field, i);
  }
  observer.CheckCookie(field, pacman.shape.getGlobalBounds());
  observer.CheckGhost(pacman.shape.getGlobalBounds(), ghosts[0].shape.getGlobalBounds(),
                      ghosts[1].shape.getGlobalBounds(), ghosts[2].shape.getGlobalBounds());
}

void render(sf::RenderWindow &window, Pacman &pacman, std::vector<Ghost> &ghosts, Observer &observer, Field &field, Paths& paths) {
  window.clear();
  if (observer.state == kVictory) {
    for (int i = 0; i < 3; ++i) {
      ghosts[i].is_stopped = true;
    }
    pacman.is_stopped = true;
    pacman.direction = kNone;
    field.DrawField(window);
    Field::DrawText(window, "YOU WON", "press ENTER to restart", sf::Color::Yellow, true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      Observer::IfEnter(window, pacman, ghosts, observer, field, paths);
    }
  } else if (observer.life_count == 0) {
    for (int i = 0; i < 3; ++i) {
      ghosts[i].is_stopped = true;
    }
    pacman.is_stopped = true;
    pacman.direction = kNone;
    field.DrawField(window);
    Field::DrawText(window, "YOU LOSE", "press ENTER to restart", sf::Color::Red, false);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      Observer::IfEnter(window, pacman, ghosts, observer, field, paths);
    }
  } else if (observer.state == kDefeat) {
    --observer.life_count;
    observer.score = std::max(0, observer.score - 50);
    observer.state = kInProcess;
    pacman.direction = kNone;
    field.DrawField(window);
    pacman.InitCreature(field, paths, 0);
    for (int i = 0; i < 3; ++i) {
      ghosts[i].InitCreature(field, paths, i);
    }
  } else {
    field.DrawField(window);
    window.draw(pacman.shape);
    for (int i = 0; i < 3; ++i) {
      window.draw(ghosts[i].shape);
    }
  }
  sf::Sprite sprite(paths.heart_texture);
  if (observer.state != kDefeat) {
    for (int i = 0; i < observer.life_count; ++i) {
      sprite.setPosition(static_cast<float>(10 + i * 32), 637);
      window.draw(sprite);
    }
  }
  std::string str = "Score: " + std::to_string(observer.score);
  sf::Text text;
  text.setString(str);
  text.setCharacterSize(27);
  text.setFillColor(sf::Color::White);
  text.setFont(paths.font);
  text.setPosition(350, 637);
  window.draw(text);
  window.display();
}

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 3;
  sf::RenderWindow window(sf::VideoMode(630, 675), "Pac-Man", sf::Style::Close, settings);
  window.setVerticalSyncEnabled(true);
  Paths paths;
  paths.InitPaths();
  Field field;
  field.InitField();
  Pacman pacman;
  pacman.InitCreature(field, paths, 0);
  std::vector<Ghost> ghosts;
  for (int i = 0; i < 3; ++i) {
    Ghost ghost;
    ghost.InitCreature(field, paths, i);
    ghosts.push_back(ghost);
  }
  Observer observer;
  sf::Clock clock;
  while (window.isOpen()) {
    handleEvents(window);
    update(clock, pacman, ghosts, observer, field);
    render(window, pacman, ghosts, observer, field, paths);
  }

  return 0;
}
