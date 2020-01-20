#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "scene_graph.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 * An entity denotes an element in the game.
 * In this game all entities are moving objects
 * so we need to to be able to set and get the velocity.
 */
class Entity : public SceneNode
{
public:
  Entity() = default;
  Entity(const Entity&) = default;
  Entity& operator=(const Entity&) = default;
  virtual ~Entity() = default;

public:
  /**
   */
  void set_velocity(sf::Vector2f velocity)
  {
    velocity_ = velocity;
  }

  /**
   */
  void set_velocity(float x, float y)
  {
    velocity_.x = x;
    velocity_.y = y;
  }

  /**
   */
  sf::Vector2f get_velocity() const noexcept
  {
    return velocity_;
  }

  /**
   * Update the position of the current entity on the scene frame.
   */
  void update_current(sf::Time dt) override
  {
    move(velocity_ * dt.asSeconds());
  }

private:
  sf::Vector2f velocity_;
};

} // END namespace arnml

#endif
