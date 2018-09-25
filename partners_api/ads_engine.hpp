#pragma once

#include "partners_api/ads_base.hpp"
#include "partners_api/banner.hpp"

#include <memory>
#include <string>
#include <vector>

namespace feature
{
class TypesHolder;
}

namespace ads
{
class Engine
{
public:
  Engine();

  bool HasBanner(feature::TypesHolder const & types,
                 storage::TCountriesVec const & countryIds,
                 std::string const & userLanguage) const;
  std::vector<Banner> GetBanners(feature::TypesHolder const & types,
                                 storage::TCountriesVec const & countryIds,
                                 std::string const & userLanguage) const;
  void IncludeAdProvider(Banner::Type const type, Banner::Place const bannerPlace);
  void ExcludeAdProvider(Banner::Type type);
  bool HasSearchBanner() const;
  std::vector<Banner> GetSearchBanners() const;

private:
  using ContainerPtr = std::unique_ptr<ContainerBase>;

  struct ContainerItem
  {
    ContainerItem(Banner::Type type, ContainerPtr && container)
      : m_type(type), m_container(std::move(container))
    {
    }

    Banner::Type m_type;
    ContainerPtr m_container;
  };

  void ExcludeAdProviderInternal(std::vector<ContainerItem> & banners, Banner::Type const type);
  void IncludeAdProviderInternal(std::vector<ContainerItem> & banners, Banner::Type const type);

  std::vector<ContainerItem> m_banners;
  std::vector<ContainerItem> m_searchBanners;
};
}  // namespace ads
