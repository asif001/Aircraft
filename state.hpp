#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include "categories.hpp"
#include "resource_holder.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

//Fwd Decl
class StateStack;
class Player;

/**
 */
class State
{
public: // public typedefs and types
  using Uptr = std::unique_ptr<State>;
  using TextureHolder = ResourceHolder<sf::Texture, textures::ID>;

  /*
   */
  struct Context
  {
    ///
    Context(sf::RenderWindow* window,
            TextureHolder* textures,
            Player* player)
      : window_(window)
      , textures_(textures)
      , player_(player)
    {
    }

    sf::RenderWindow* window_   = nullptr;
    TextureHolder*    textures_ = nullptr;
    Player*           player_   = nullptr;
  };

public: //'tors
  /**
   */
  explicit State(StateStack* ss, Context ctx)
    : state_stack_(ss)
    , ctx_(ctx)
  {
  }

  State(const State&) = delete;
  State& operator=(const State&) = delete;

  virtual ~State() = default;

public: // Interface APIs
  ///
  virtual void draw() = 0;
  ///
  virtual bool update(sf::Time dt) = 0;
  ///
  virtual bool handle_event(sf::Event event) = 0;

protected: // Implementations
  ///
  void request_stack_push(Category::States id);
  ///
  void request_stack_pop();
  ///
  void request_state_clear();
  ///
  Context get_ctx() const noexcept
  {
    return ctx_;
  }

private:
  ///
  StateStack* state_stack_ = nullptr;
  ///
  Context     ctx_;

};

} // END namespace arnml

#include "impl/state.ipp"

#endif
