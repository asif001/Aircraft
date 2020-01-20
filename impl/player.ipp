#ifndef PLAYER_IPP
#define PLAYER_IPP

#include "../player.hpp"
#include "../aircraft.hpp"
#include "../utility.hpp"
#include "../categories.hpp"

namespace arnml {

Player::Player()
{
  key_to_action_bindings_[sf::Keyboard::Up]    = Action::MoveUp;
  key_to_action_bindings_[sf::Keyboard::Down]  = Action::MoveDown;
  key_to_action_bindings_[sf::Keyboard::Left]  = Action::MoveLeft;
  key_to_action_bindings_[sf::Keyboard::Right] = Action::MoveRight;

  init_actions();

  for (auto& elem : action_2_cmd_bindings_) {
    elem.second.category_ = Category::Type::PlayerAircraft;
  }
}

void Player::handle_event(sf::Event event, CommandQueue& cmd_q)
{
  if (event.type == sf::Event::KeyPressed) {
    auto found = key_to_action_bindings_.find(event.key.code);

    if (found != key_to_action_bindings_.end()) {
      /// Check if its a real time event or not
      //Only non real time event are handled ehere
      if (!is_real_time_action(found->second)) {
        cmd_q.push(action_2_cmd_bindings_[found->second]);
      }
    }
  }
}

void Player::handle_realtime_input(CommandQueue& cmd_q)
{
  for (auto& elem : key_to_action_bindings_) {
    if (is_real_time_action(elem.second) && sf::Keyboard::isKeyPressed(elem.first))
    {
      cmd_q.push(action_2_cmd_bindings_[elem.second]);
    }
  }
}

void Player::init_actions()
{
  action_2_cmd_bindings_[Action::MoveLeft].action_ = derived_action<Aircraft>(AircraftMover{-1, 0});
  action_2_cmd_bindings_[Action::MoveRight].action_ = derived_action<Aircraft>(AircraftMover{+1, 0});
  action_2_cmd_bindings_[Action::MoveUp].action_ = derived_action<Aircraft>(AircraftMover{0, -1});
  action_2_cmd_bindings_[Action::MoveDown].action_ = derived_action<Aircraft>(AircraftMover{0, +1});
}

bool Player::is_real_time_action(Action action)
{
  switch (action) {
  case Action::MoveLeft:
  case Action::MoveRight:
  case Action::MoveUp:
  case Action::MoveDown:
    return true;
  default:
    return false;
  };

  assert (0 && "Code not reached");
}

} // END namespace arnml

#endif
