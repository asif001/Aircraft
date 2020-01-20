#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "state.hpp"

namespace arnml {

/**
 */
class TitleState: public State
{
public:
  ///
  TitleState(StateStack& ss, Context ctx);

  TitleState(const TitleState&) = default;
  TitleState& operator=(const TitleState&) = default;

  ~TitleState() = default;
public:
  ///
  virtual void draw() override;
  ///
  virtual bool update(sf::Time dt) override;
  ///
  virtual bool handle_event(sf::Event event) override;

private:
  sf::Sprite background_sprite_;
  sf::Text   text_;
  sf::Time   text_effect_time_ = sf::Time::Zero;
  bool       show_text_ = true;
};


}

#include "impl/title_screen.ipp"

#endif
