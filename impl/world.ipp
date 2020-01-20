#ifndef WORLD_IPP
#define WORLD_IPP

#include "../world.hpp"
#include "SFML/System/String.hpp"
#include "../resource_holder.hpp"

namespace arnml {

World::World(sf::RenderWindow& w)
  : window_(w)
  , world_view_(window_.getDefaultView())
  , world_bounds_(
      0.f,                        //left X position
      0.f,                        //top Y position
      world_view_.getSize().x,    //width
      2000.f)                     //height
  , start_pos_(
      world_view_.getSize().x / 2.f,
      world_bounds_.height - world_view_.getSize().y / 2.f)
{
  load_textures();
  build_scene();
  world_view_.setCenter(start_pos_);
}

void World::load_textures()
{
  textures_.load_resource(textures::ID::Eagle, sf::String{"./images/Eagle.png"});
  textures_.load_resource(textures::ID::Desert, sf::String{"./images/Desert.png"});
  textures_.load_resource(textures::ID::Raptor, sf::String{"./images/Raptor.png"});
}

void World::build_scene()
{
  for (size_t i = 0; i < LayerCount; i++) {
    std::unique_ptr<SceneNode> ptr{new SceneNode{}};
    scene_layers_[i] = ptr.get();
    scene_graph_.add_child(std::move(ptr));
  }

  //prepare the tiled background
  sf::Texture& bg = textures_.get(textures::ID::Desert);
  bg.setRepeated(true);

  //Add the backgraound sprite to the scene
  sf::IntRect texture_rect{world_bounds_};
  std::unique_ptr<SpriteNode> bgsprite{new SpriteNode(bg, texture_rect)};
  bgsprite->setPosition(world_bounds_.left, world_bounds_.top);
  scene_layers_[Background]->add_child(std::move(bgsprite));

  //Add the leader aircraft
  std::unique_ptr<Aircraft> leader{new Aircraft{textures::ID::Eagle, textures_}};
  player_ = leader.get();
  player_->setPosition(start_pos_);
  player_->set_velocity(0.f, scroll_speed_);
  scene_layers_[Air]->add_child(std::move(leader));

  //Adding left escort
  std::unique_ptr<Aircraft> left_escort{new Aircraft{textures::ID::Raptor, textures_}};
  left_escort->setPosition(-80.f, 50.f);
  player_->add_child(std::move(left_escort));

  //Add right escort
  std::unique_ptr<Aircraft> right_escort{new Aircraft{textures::ID::Raptor, textures_}};
  right_escort->setPosition(80.f, 50.f);
  player_->add_child(std::move(right_escort));
}

void World::draw()
{
  window_.setView(world_view_);
  window_.draw(scene_graph_);
}

void World::update(sf::Time dt)
{
  world_view_.move(0.f, scroll_speed_ * dt.asSeconds());

  sf::Vector2f position = player_->getPosition();
  sf::Vector2f velocity = player_->get_velocity();

  if (position.x < world_bounds_.left + 150
      || position.x >= world_bounds_.left + world_bounds_.width - 150) {
    velocity.x = -1 * velocity.x;
    player_->set_velocity(velocity);
  }

  while (!cmd_q_.is_empty()) {
    scene_graph_.on_command(cmd_q_.pop(), dt);
  }

  scene_graph_.update(dt);
}

} //END namespace arnml

#endif
