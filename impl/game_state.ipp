#ifndef GAME_STATE_IPP
#define GAME_STATE_IPP

#include "../game_state.hpp"

namespace arnml {

void GameState::draw()
{
  world_.draw();
}

bool GameState::update(sf::Time dt)
{
  world_.update(dt);
  auto& commands = world_.get_command_q();
  player_->handle_realtime_input(commands);
  return true;
}

bool GameState::handle_event(sf::Event event)
{
  auto& commands = world_.get_command_q();
  player_->handle_event(event, commands);

  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
  {
    request_stack_push(Category::States::Pause);
  }
  return true;
}

} // END namespace arnml

#endif
