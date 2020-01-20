#ifndef APPLICATION_IPP
#define APPLICATION_IPP

#include "../application.hpp"

namespace arnml {

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
  : window_(sf::VideoMode(1024, 768), "Gameplay", sf::Style::Close)
  , textures_()
  , stack_(State::Context{&window_, &textures_, &player_})
{
  register_states();
  stack_.push_state(Category::States::Title);
}

void Application::register_states()
{
  stack_.register_state<TitleState>(Category::States::Title);
  stack_.register_state<MenuState>(Category::States::Menu);
  stack_.register_state<GameState>(Category::States::Game);
  stack_.register_state<PauseState>(Category::States::Pause);
}

void Application::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (window_.isOpen()) {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;

    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      process_input();
      update(TimePerFrame);

      if (stack_.is_empty()) {
        window_.close();
      }
    }

    render();
  }
  return;
}

void Application::process_input()
{
  sf::Event event;

  while (window_.pollEvent(event)) {
    stack_.handle_event(event);

    if (event.type == sf::Event::Closed) {
      window_.close();
    }
  }

  return;
}

void Application::render()
{
  stack_.draw();
}

void Application::update(sf::Time dt)
{
  stack_.update(dt);
}

} // END namespace arnml

#endif
