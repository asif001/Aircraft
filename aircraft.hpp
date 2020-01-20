#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "entity.hpp"
#include "categories.hpp"
#include "resource_identifiers.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 */
class Aircraft: public Entity
{
public:
  /**
   */
  template <typename ResourceHolder>
  explicit Aircraft(textures::ID type, ResourceHolder& res_hldr)
    : type_(type)
  {
    auto& resource = res_hldr.get(type);
    aircraft_.setTexture(resource);
    sf::FloatRect bounds = aircraft_.getLocalBounds();
    aircraft_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
  }

  Aircraft(const Aircraft& other) = default;
  Aircraft& operator=(const Aircraft& other) = default;

  ~Aircraft() = default;

public:
  /**
   */
  virtual void draw_current(sf::RenderTarget& target,
                            sf::RenderStates states) const override
  {
    target.draw(aircraft_, states);
  }

  /**
   */
  virtual uint32_t category() const noexcept override
  {
    switch (type_) {
    case textures::ID::Eagle:
      return Category::PlayerAircraft;
    default:
      return Category::EnemyAircraft;
    };

    assert (0 && "Code Not Reached");
  }

  /**
   */
  void accelerate(sf::Vector2f velocity)
  {
    this->set_velocity(this->get_velocity() + velocity);
  }

private:
  /// Type of aircraft
  textures::ID type_;
  ///
  sf::Sprite aircraft_;
};


/**
 * Aircraft mover action class.
 * Called in response to an action
 */
struct AircraftMover
{
  AircraftMover(float x, float y)
    : velocity_(x, y)
  {
  }

  void operator()(Aircraft& ac, sf::Time dt) const
  {
    (void)dt;
    ac.accelerate(velocity_);
  }

  sf::Vector2f velocity_;
};

} // END namespace arnml

#endif
