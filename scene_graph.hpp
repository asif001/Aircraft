#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>

#include "command.hpp"
#include "categories.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 * An element in the image transform hierarchy
 * in a scene.
 */
class SceneNode: public sf::Transformable
               , public sf::Drawable
{
public:
  SceneNode() = default;

  SceneNode(const SceneNode& other) = delete;
  SceneNode& operator=(const SceneNode& other) = delete;

  virtual ~SceneNode() = default;

public:
  ///Get number of children under this
  ///scene node.
  size_t num_children() const noexcept
  {
    return children_.size();
  }

  /**
   * Get the parent SceneNode.
   * nullptr for the topmost SceneNode.
   */
  SceneNode* parent() noexcept
  {
    return parent_;
  }

  const SceneNode* parent() const noexcept
  {
    return parent_;
  }

  /**
   * Add and remove children.
   */
  void add_child(std::unique_ptr<SceneNode> ptr)
  {
    ptr->parent_ = this;
    children_.emplace_back(std::move(ptr));
  }

  /// Remove a specific node from children.
  /// Returns nullptr wrapped inside unique_ptr if
  /// not found.
  std::unique_ptr<SceneNode> detach_child(const SceneNode& node)
  {
    auto itr = std::find_if(std::begin(children_), std::end(children_),
                            [&](const std::unique_ptr<SceneNode>& elem) {
                              return std::addressof(node) == elem.get();
                           });

    assert (itr != std::end(children_));

    if (itr == std::end(children_)) {
      return {nullptr};
    }
    auto res = std::move(*itr);
    children_.erase(itr);

    return res;
  }

  /**
   * Update the scene
   */
  void update(sf::Time dt)
  {
    update_current(dt);
    update_children(dt);
  }

  /**
   * Get the category of the game object.
   */
  virtual uint32_t category() const noexcept
  {
    return Category::Scene;
  }

  /**
   * Execute the command
   */
  void on_command(const Command& cmd, sf::Time dt)
  {
    if (category() & cmd.category_) {
      cmd.action_(*this, dt);
    }
    
    for (auto& e : children_) e->on_command(cmd, dt);
  }

  /**
   */
  virtual void set_position(float x, float y)
  {
    (void)x;
    (void)y;
  }

private:
  /**
   */
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override
  {
    // states.transform holds the information about
    // where to render the parent scene node.
    // operator*= combines the parents absolute transform
    // with the current nodes relative one resulting in
    // absolute transform of the current node.
    states.transform *= this->getTransform();

    draw_current(target, states);

    //Draw all the child nodes
    for (auto& e : children_) e->draw(target, states);
  }

  /**
   */
  virtual void draw_current(sf::RenderTarget& target,
                            sf::RenderStates states) const
  {
    // Do nothing
    // Upto the derived implementations
  }

  /**
   */
  virtual void update_current(sf::Time dt)
  {
    // Do nothing
    // Upto the derived implementation
    (void)dt;
  }

  /**
   */
  void update_children(sf::Time dt)
  {
    for (auto& e : children_) e->update(dt);
  }

  /**
   */
  sf::Transform get_world_transform() const
  {
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* n = this; n; n = n->parent_)
    {
      transform = transform * getTransform();
    }
    return transform;
  }

  /**
   * Gets the absolute position of an object.
   * this->getPosition() gives the relative position w.r.t
   * top level object.
   * We will traverse up the graph using the parent_ pointer
   * to accumulate the relative positions.
   */
  sf::Vector2f get_world_position() const
  {
    return get_world_transform() * sf::Vector2f{};
  }

private:
  std::vector<std::unique_ptr<SceneNode>> children_;
  SceneNode* parent_ = nullptr;
};

/**
 */
class SceneGraph
{
public:
  SceneGraph() = default;

public:
  /**
   * Get the top scene node
   */
  SceneNode* get_root() noexcept
  {
    return root_.get();
  }

  /**
   */
  const SceneNode* get_root() const noexcept
  {
    return root_.get();
  }

private:
  std::unique_ptr<SceneNode> root_;
};


}

#endif
