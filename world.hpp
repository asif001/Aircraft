#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "entity.hpp"
#include "player.hpp"
#include "command.hpp"
#include "aircraft.hpp"
#include "scene_graph.hpp"
#include "sprite_node.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"

#include "SFML/System/String.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

using TextureHolder = ResourceHolder<sf::Texture, textures::ID>;

/**
 */
class World
{
public:
  /**
   */
  explicit World(sf::RenderWindow& w);

  /// Disable copy and assignment
  World(const World& other) = delete;
  World& operator=(const World& other) = delete;

  ~World() = default;

public:
  ///
  void update(sf::Time dt);

  ///
  void draw();

  ///
  CommandQueue& get_command_q() noexcept
  {
    return cmd_q_;
  }

private:
  ///
  void load_textures();

  ///
  void build_scene();

private:
  /**
   */
  enum Layer
  {
    Background,
    Air,
    LayerCount,
  };

private:
  ///
  sf::RenderWindow& window_;
  ///
  TextureHolder     textures_;
  ///
  sf::View          world_view_;
  ///
  SceneNode         scene_graph_;
  ///
  std::array<SceneNode*, LayerCount> scene_layers_;

  ///
  sf::FloatRect world_bounds_;
  ///
  sf::Vector2f  start_pos_;
  ///
  float         scroll_speed_ = -100.f;
  ///
  Aircraft*     player_ = nullptr;
  ///
  CommandQueue  cmd_q_;
};

} // END namespace arnml

#include "impl/world.ipp"

#endif
