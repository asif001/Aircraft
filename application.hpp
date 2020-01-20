#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "state_stack.hpp"
#include "player.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 */
class Application
{
public:
  Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  ~Application() = default;

public: // Public APIs
  ///
  void run();

private: // Private APIS
  ///
  static const sf::Time TimePerFrame;
  ///
  void register_states();
  ///
  void process_input();
  ///
  void render();
  ///
  void update(sf::Time dt);

private: // Data members
  ///
  sf::RenderWindow window_;
  ///
  State::TextureHolder textures_;
  ///
  Player               player_;
  ///
  StateStack stack_;
};


} // END namespace arnml

#endif
