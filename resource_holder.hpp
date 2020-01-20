#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <exception>

#include "resource_identifiers.hpp"
#include "SFML/Graphics.hpp"

namespace arnml {

/**
 * A container to hold a resource of type
 * `ResourceType` and identified by the enum class
 * `ResourceID` template parameter.
 */
template <typename ResourceType, typename ResourceID>
class ResourceHolder
{
public:
  ResourceHolder() = default;
  ResourceHolder(const ResourceHolder& other) = delete;
  ResourceHolder& operator=(const ResourceHolder&) = delete;

public:
  /**
   * Loads a resource into the resource map.
   * If the resource loading fails it returns false.
   */
  bool load_resource(ResourceID id, const std::string& filename);

  /**
   * Removes a resource from the map.
   */
  bool remove_resource(ResourceID id)
  {
    return res_map_.erase(id);
  }

  /**
   * Gets a resource from the map.
   * Precondition is that the resource ID
   * should already be present in the map.
   */
  ResourceType& get(ResourceID id)
  {
    auto itr = res_map_.find(id);
    assert (itr != std::end(res_map_));

    return *(itr->second.get());
  }

  const ResourceType& get(ResourceID id) const
  {
    auto itr = res_map_.find(id);
    assert (itr != std::end(id));

    return *(itr->second.get());
  }

private:
  /// Maps resource ID to actual resource
  std::map<ResourceID, std::unique_ptr<ResourceType>> res_map_;
};

} // END namespace arnml

#include "impl/resource_holder.ipp"

#endif 
