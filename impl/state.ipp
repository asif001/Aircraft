#ifndef STATE_IPP
#define STATE_IPP

#include "../state.hpp"
#include "../state_stack.hpp"

namespace arnml {

void State::request_stack_push(Category::States id)
{
  state_stack_->push_state(id);
}

void State::request_stack_pop()
{
  state_stack_->pop_state();
}

void State::request_state_clear()
{
  state_stack_->clear_states();
}

} // END namespace arnml

#endif
