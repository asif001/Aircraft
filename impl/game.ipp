#include <cassert>
#include "../game.hpp"

namespace arnml {

Game::Game()
  : window_(sf::VideoMode{640, 480}, "My Game")
  , world_(window_)
{
}

template <typename Resource, typename ResourceID, typename ResourceLoader>
void Game::create_entity(ResourceID id, ResourceLoader& loader)
{
  assert (0 && "Code not used");
}

void Game::run()
{
  sf::Clock clock;

  while (window_.isOpen()) {
    sf::Time delta = clock.restart();
    process_events();
    update(delta);
    render();
  }
  return;
}

void Game::process_events()
{
  sf::Event event;
  auto& cmd_q = world_.get_command_q();

  while (window_.pollEvent(event)) {
    player_.handle_event(event, cmd_q);

    if (event.type == sf::Event::Closed) {
      window_.close();
      break;
    }
  }

  player_.handle_realtime_input(cmd_q);

  return;
}

void Game::update(sf::Time delta)
{
  world_.update(delta);
  return;
}

void Game::render()
{
  window_.clear();
  world_.draw();
  window_.display();
  return;
}

void Game::handle_key_press(sf::Keyboard::Key key, bool key_pressed)
{
  switch (key) {
  case sf::Keyboard::W:
  case sf::Keyboard::Up: 
    is_moving_up_ = key_pressed;
    break;
  case sf::Keyboard::S:
  case sf::Keyboard::Down:
    is_moving_down_ = key_pressed;
    break;
  case sf::Keyboard::D:
  case sf::Keyboard::Right:
    is_moving_right_ = key_pressed;
    break;
  case sf::Keyboard::A:
  case sf::Keyboard::Left:
    is_moving_left_ = key_pressed;
    break;
  default:
    break;
  };
  return;
}

} // END namespace arnml
