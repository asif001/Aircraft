#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <queue>
#include <cassert>
#include <functional>
#include "categories.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {
//Fwd Decl
class SceneNode;

/**
 * Command class.
 * Sends message/commands to the correct
 * category.
 */
struct Command
{
  /**
   */
  Command() = default;
  ///
  std::function<void(SceneNode&, sf::Time)> action_;
  ///
  uint32_t category_ = Category::None;
};


/**
 * Queue of Commands
 */
class CommandQueue
{
public:
  CommandQueue() = default;

  /**
   */
  void push(const Command& cmd)
  {
    cmd_q_.push(cmd);
  }

  /**
   */
  Command pop()
  {
    assert (not cmd_q_.empty());
    auto ret = cmd_q_.front();
    cmd_q_.pop();
    return ret;
  }

  /**
   */
  bool is_empty() const noexcept
  {
    return cmd_q_.empty();
  }

private:
  std::queue<Command> cmd_q_;
};

}

#endif
