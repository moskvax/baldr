#ifndef VALHALLA_MIDGARD_TILEHIERARCHY_H
#define VALHALLA_MIDGARD_TILEHIERARCHY_H

#include <map>
#include <string>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <valhalla/midgard/pointll.h>
#include <valhalla/midgard/tiles.h>
#include <valhalla/baldr/graphid.h>
#include <valhalla/baldr/graphconstants.h>

namespace valhalla {
namespace baldr {


/**
 * class used to get information about a given hierarchy of tiles
 */
class TileHierarchy {
 public:
  /**
   * Constructor
   */
  TileHierarchy(const boost::property_tree::ptree& pt);

  /**
   * Encapsulates a few types together to define a level in the hierarchy
   */
  struct TileLevel{
    TileLevel(const boost::property_tree::ptree& pt);
    TileLevel(const uint8_t level, const std::string& name,
              const RoadClass importance, const midgard::Tiles<midgard::PointLL>& tiles);
    bool operator<(const TileLevel& other) const;
    uint8_t level;
    RoadClass importance;
    std::string name;
    midgard::Tiles<midgard::PointLL> tiles;
  };

  /**
   * Get the set of levels in this hierarchy
   *
   * @return set of TileLevel objects
   */
  const std::map<uint8_t, TileLevel>& levels() const;

  /**
   * Get the root tile directory where the tiles are stored
   *
   * @return string directory
   */
  const std::string& tile_dir() const;

  /**
   * Returns true if the level exists in the hierarchy
   *
   * @param level  the level to check
   * @return boolean  whether the level is in the hierarchy or not
   */
  bool HasLevel(const uint8_t level) const;

  /**
   * Returns the graphid of the requested tile based on a lat,lng and a level
   * if the level is not supported an invalid id will be returned
   *
   * @param pointll a lat,lng location within the tile
   * @param level   the level of the requested tile
   */
  GraphId GetGraphId(const midgard::PointLL& pointll, const uint8_t level) const;

 private:
  explicit TileHierarchy();

  // a place to keep each level of the hierarchy
  std::map<uint8_t, TileLevel> levels_;
  // the tiles are stored
  std::string tile_dir_;
};

}
}

#endif  // VALHALLA_MIDGARD_TILEHIERARCHY_H
