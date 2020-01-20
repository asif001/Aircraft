#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cassert>
#include <functional>
#include "SFML/Graphics.hpp"

namespace arnml {

//Fwd Decl
class SceneNode;

/**
 * Wraps a functor to make it receive
 * its arguments in a typesafe manner.
 *
 * Template arguments:
 * 1. Fn - Auto deducted.
 * 2. GObj - The game object to be casted to from SceneNode.
 */
template <typename GObj, typename Fn>
std::function<void (SceneNode&, sf::Time)>
derived_action(Fn f)
{
  return [=](SceneNode& n, sf::Time dt) {
    assert (dynamic_cast<GObj*>(&n) != nullptr);
    auto& obj = static_cast<GObj&>(n);
    f(obj, dt);
  };
}

} // END namespace arnml

#endif
