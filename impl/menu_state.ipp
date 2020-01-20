#ifndef MENU_STATE_IPP
#define MENU_STATE_IPP

#include "../menu_state.hpp"

namespace arnml {

MenuState::MenuState(StateStack& ss, Context ctx)
  : State(&ss, ctx)
{
  sf::Text play;
  play.setString("Play");
  play.setPosition(100, 300);
  options_.push_back(play);

  sf::Text exit;
  exit.setString("Exit");
  exit.setPosition(100, 350);
  options_.push_back(exit);
}

void MenuState::draw()
{
  sf::RenderWindow& window = *get_ctx().window_;
  window.draw(background_sprite_);

  for (auto& text : options_) window.draw(text);
}

bool MenuState::update(sf::Time dt)
{
  (void) dt;
  return true;
}

bool MenuState::handle_event(sf::Event event)
{
  switch (event.key.code) {
  case sf::Keyboard::Up:
  {
    if (option_index_ == 0) return true;
    else option_index_--;

    update_option_text();
    break;
  }
  case sf::Keyboard::Down:
  {
    if (option_index_ == options_.size() - 1) return true;
    else option_index_++;

    update_option_text();
    break;
  }
  case sf::Keyboard::Return:
  {
    if (option_index_ == static_cast<size_t>(OptionNames::Play)) {
      request_stack_pop();
      request_stack_push(Category::States::Game);
    } else {
      request_stack_pop();
    }
    break;
  }
  default:
    break;
  };

  return true;
}

void MenuState::update_option_text()
{
  if (options_.empty()) return;
  for (auto& text : options_) text.setOutlineColor(sf::Color::White);
  options_[option_index_].setOutlineColor(sf::Color::Green);
}

} // END namespace arnml


#endif
