#include <SFML/Graphics.hpp>

class Paths {
public:
  sf::Texture pacman_texture;
  sf::Texture ghosts_texture;
  sf::Texture heart_texture;
  sf::Font font;
  
  void InitPaths() {
    pacman_texture.loadFromFile("../assets/pacman.jpg");
    ghosts_texture.loadFromFile("../assets/ghosts.jpg");
    heart_texture.loadFromFile("../assets/heart.jpg");
    font.loadFromFile("../assets/font.ttf");
  }
};

