#ifndef GAME_HPP
#define GAME_HPP

#include "world.hpp"
#include "player.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 */
class Game
{
public:
  /// Constructor
  Game();

  ~Game() = default;

  /**
   * Non copyable and assignable
   */
  Game(const Game& other) = delete;
  Game& operator=(const Game& other) = delete;

public:
  /**
   */
  template <typename Resource, typename ResourceID, typename ResourceLoader>
  void create_entity(ResourceID id, ResourceLoader& loader);

  /**
   */
  void run();

private:
  /**
   */
  void process_events();

  /**
   */
  void update(sf::Time delta);

  /**
   */
  void render();

  /**
   */
  void handle_key_press(sf::Keyboard::Key k, bool key_pressed);

private:
  /// Rendering window
  sf::RenderWindow window_;

  /// World
  World world_;

  /// TODO: multiple entities
  //std::unique_ptr<Entity> entity_ = nullptr;

  //position
  bool is_moving_up_    = false;
  bool is_moving_down_  = false;
  bool is_moving_right_ = false;
  bool is_moving_left_  = false;

  ///
  Player player_;
};

} // END namespace arnml

#include "impl/game.ipp"

#endif
