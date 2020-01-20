#ifndef STATE_STACK_IPP
#define STATE_STACK_IPP

#include <cassert>
#include "../state_stack.hpp"

namespace arnml {

template <typename StateT>
bool StateStack::register_state(Category::States state_id)
{
  auto creator = [this]() {
    return State::Uptr{new StateT{this, this->ctx_}};
  };

  auto ret = factory_.insert({state_id, creator});
  assert (ret.second && "Duplicate entry should not be present");
  return ret.second;
}

State::Uptr
StateStack::create_state(Category::States id)
{
  auto itr = factory_.find(id);
  assert (itr != std::end(factory_));

  return itr->second();
}

void StateStack::push_state(Category::States id)
{
  pending_list_.push_back(PendingChange{Action::PUSH, id});
}

void StateStack::pop_state()
{
  pending_list_.push_back(PendingChange{Action::POP});
}

void StateStack::clear_states()
{
  pending_list_.push_back(PendingChange{Action::CLEAR});
}

void StateStack::handle_event(sf::Event event)
{
  for (auto& state : stack_) {
    if (!state->handle_event(event)) break;
  }

  apply_pending_changes();
  return;
}

void StateStack::update(sf::Time dt)
{
  for (auto& state : stack_) {
    state->update(dt);
  }

  apply_pending_changes();
  return;
}

void StateStack::draw()
{
  for (auto& state : stack_) {
    state->draw();
  }
  return;
}

void StateStack::apply_pending_changes()
{
  for (auto& pelem : pending_list_) {
    switch (pelem.action_) {
    case StateStack::Action::PUSH:
    {
      stack_.push_back(create_state(pelem.state_id_));
      break;
    }
    case StateStack::Action::POP:
    {
      stack_.pop_back();
      break;
    }
    case StateStack::Action::CLEAR:
    {
      stack_.clear();
      break;
    }
    default:
      assert (0 && "CODE NOT REACHED");
    };
  }

  pending_list_.clear();
  return;
}

} // END namespace arnml

#endif
