#ifndef RESOURCE_HOLDER_IPP
#define RESOURCE_HOLDER_IPP

namespace arnml {

template <typename ResourceType, typename ResourceID>
bool ResourceHolder<ResourceType, ResourceID>::load_resource(
    ResourceID id, const std::string& filename)
{
  std::unique_ptr<ResourceType> res{new ResourceType{}};
  if (!res->loadFromFile(filename)) {
    return false;
  }

  auto ok = res_map_.insert(std::make_pair(id, std::move(res)));
  assert (ok.second);

  return true;
}

}

#endif
