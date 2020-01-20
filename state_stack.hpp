#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <map>
#include <vector>
#include <functional>
#include "state.hpp"

namespace arnml {

/**
 */
class StateStack
{
public:
  enum class Action
  {
    PUSH,
    POP,
    CLEAR,
  };

public:
  ///
  explicit StateStack(State::Context ctx)
    : ctx_(ctx)
  {
  }

  StateStack(const StateStack&) = delete;
  StateStack& operator=(const StateStack&) = delete;

  ~StateStack() = default;

public:
  ///
  template <typename StateT>
  bool register_state(Category::States state_id);
  ///
  void push_state(Category::States id);
  ///
  void pop_state();
  ///
  void clear_states();
  ///
  bool is_empty() const noexcept
  {
    return stack_.size();
  }

  ///
  void update(sf::Time dt);
  ///
  void draw();
  ///
  void handle_event(sf::Event event);

private:
  ///
  State::Uptr create_state(Category::States id);
  ///
  void apply_pending_changes();

private:
  ///
  struct PendingChange
  {
    explicit PendingChange(Action act, Category::States id = Category::States::None)
      : action_(act)
      , state_id_(id)
    {
    }
    Action action_;
    Category::States state_id_;
  };

private:
  ///
  State::Context ctx_;
  ///
  std::vector<State::Uptr> stack_;
  ///
  std::vector<PendingChange> pending_list_;
  ///
  std::map<Category::States, std::function<State::Uptr()>> factory_;
};


} // END namespace arnml

#include "impl/state_stack.ipp"


#endif
