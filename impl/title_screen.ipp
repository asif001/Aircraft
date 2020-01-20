#ifndef TITLE_SCREEN_IPP
#define TITLE_SCREEN_IPP

#include "../title_state.hpp"

namespace arnml {

TitleState::TitleState(StateStack& ss, Context ctx)
  : State(&ss, ctx)
{
}

void TitleState::draw()
{
  sf::RenderWindow& window = *get_ctx().window_;
  window.draw(background_sprite_);

  if (show_text_) window.draw(text_);
}

bool TitleState::update(sf::Time dt)
{
  text_effect_time_ += dt;
  if (text_effect_time_ >= sf::seconds(0.5f)) {
    show_text_ = !show_text_;
    text_effect_time_ = sf::Time::Zero;
  }
  return true;
}

bool TitleState::handle_event(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed) {
    request_stack_pop();
    request_stack_push(Category::States::Menu);
  }
  return true;
}

} // END namespace arnml

#endif
