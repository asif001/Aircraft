#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "state.hpp"
#include "state_stack.hpp"

namespace arnml {

class PauseState: public State
{
public:
  ///
  PauseState(StateStack& ss, Context ctx);

  void draw() override;

  bool update(sf::Time dt) override;

  bool handle_event(sf::Event event) override;

private:
  ///
  sf::Sprite background_sprite_;
  sf::Text paused_text_;
  sf::Text instruction_text_;
};

} // END namespace arnml

#include "impl/pause_state.ipp"

#endif
