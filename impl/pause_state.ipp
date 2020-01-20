#ifndef PAUSE_STATE_IPP
#define PAUSE_STATE_IPP

#include "../pause_state.hpp"
#include "../categories.hpp"

namespace arnml {

PauseState::PauseState(StateStack& ss, Context ctx)
  : State(&ss, ctx)
{
  paused_text_.setString("Game Paused");
  sf::Vector2f viewSize = ctx.window_->getView().getSize();
  paused_text_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

  instruction_text_.setString("Press backspace to continue playing");
  instruction_text_.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
  sf::RenderWindow& w = *get_ctx().window_;
  w.setView(w.getDefaultView());

  sf::RectangleShape backgroundShape;
  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  backgroundShape.setSize(w.getView().getSize());

  w.draw(backgroundShape);
  w.draw(paused_text_);
  w.draw(instruction_text_);
}

bool PauseState::update(sf::Time dt)
{
  (void)dt;
  return false;
}

bool PauseState::handle_event(sf::Event event)
{
  if (event.type != sf::Event::KeyPressed) {
    return false;
  }

  if (event.key.code == sf::Keyboard::Escape) {
    request_stack_pop();
  }
  if (event.key.code == sf::Keyboard::BackSpace) {
    request_state_clear();
    request_stack_push(Category::States::Game);
  }
  return true;
}

} // END namespace arnml

#endif
