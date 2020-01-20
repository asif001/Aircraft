#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <vector>
#include "state.hpp"

namespace arnml {

/**
 */
class MenuState: public State
{
public:
  enum class OptionNames
  {
    Play,
    Exit,
  };

public:
  ///
  MenuState(StateStack& ss, Context ctx);

  MenuState(const MenuState&) = default;
  MenuState& operator=(const MenuState&) = default;

  ~MenuState() = default;

public:
  ///
  void draw() override;
  ///
  bool update(sf::Time dt) override;
  ///
  bool handle_event(sf::Event event) override;

private:
  ///
  void update_option_text();

private:
  ///
  sf::Sprite background_sprite_;
  ///
  std::vector<sf::Text> options_;
  ///
  size_t option_index_ = 0;
};


} // END namespace arnml

#include "impl/menu_state.ipp"


#endif
