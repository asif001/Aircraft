#ifndef CATEGORIES_HPP
#define CATEGORIES_HPP

namespace arnml {

namespace Category {
  /**
   * Types of aircraft entities in the
   * game.
   */
  enum Type
  {
    None = 0,
    Scene,
    PlayerAircraft,
    AlliedAircraft,
    EnemyAircraft,
  };


  /**
   */
  enum class States
  {
    None,
    Title,
    Menu,
    Game,
    Pause,
  };
}

} //END namespace arnml

#endif
