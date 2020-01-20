#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>

#include "command.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 * A player class for handling
 * inputs.
 * Abstracts the input handling from the game processing
 * loop in game
 */
class Player
{
public:
  ///
  Player();
  ~Player() = default;

public:

  /**
   * Actions to respond to
   */
  enum class Action
  {
    MoveUp = 0,
    MoveDown,
    MoveLeft,
    MoveRight,
  };

public:
  /**
   * Handles event for a player.
   */
  void handle_event(sf::Event event, CommandQueue& cmd_q);

  /**
   * Handle real time inputs for a player
   */
  void handle_realtime_input(CommandQueue& cmd_q);

private:
  /// Initialize action_2_cmd_bindings_ with relevent actions
  void init_actions();

  // Check if the event is real time action or not
  bool is_real_time_action(Action action);

private:
  std::map<sf::Keyboard::Key, Action> key_to_action_bindings_;
  std::map<Action, Command> action_2_cmd_bindings_;
};

} // END namespace arnml

#include "impl/player.ipp"

#endif
