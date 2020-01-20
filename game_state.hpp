#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "state.hpp"
#include "world.hpp"

namespace arnml {

/**
 */
class GameState : public State
{
public:
  ///
  GameState(StateStack& stack, Context ctx)
    : State(&stack, ctx)
    , world_(*ctx.window_)
    , player_(ctx.player_)
  {
  }
  ///
  ~GameState() = default;

public:
  ///
  void draw() override;
  ///
  bool update(sf::Time dt) override;
  ///
  bool handle_event(sf::Event event) override;

private: // private data members
  World   world_;
  Player* player_;
};

}

#endif
