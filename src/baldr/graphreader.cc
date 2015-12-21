#include "baldr/graphreader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <boost/filesystem.hpp>

#include <valhalla/midgard/logging.h>
#include "baldr/connectivity_map.h"
using namespace valhalla::baldr;

namespace {
  constexpr size_t DEFAULT_MAX_CACHE_SIZE = 1073741824; //1 gig
  constexpr size_t AVERAGE_TILE_SIZE = 2097152; //2 megs
  const GraphTile* NO_TILE = nullptr;
}

namespace valhalla {
namespace baldr {

//this constructor delegates to the other
GraphReader::GraphReader(const boost::property_tree::ptree& pt):tile_hierarchy_(pt), cache_size_(0) {
  max_cache_size_ = pt.get<size_t>("max_cache_size", DEFAULT_MAX_CACHE_SIZE);

  //assume avg of 10 megs per tile
  cache_.reserve(max_cache_size_/AVERAGE_TILE_SIZE);
}

GraphReader::GraphReader() {}

// Method to test if tile exists
bool GraphReader::DoesTileExist(const GraphId& graphid) const {
  return DoesTileExist(tile_hierarchy_, graphid);
}
bool GraphReader::DoesTileExist(const TileHierarchy& tile_hierarchy, const GraphId& graphid) {
  std::string file_location = tile_hierarchy.tile_dir() + "/" +
    GraphTile::FileSuffix(graphid.Tile_Base(), tile_hierarchy);
  struct stat buffer;
  return stat(file_location.c_str(), &buffer) == 0;
}

bool GraphReader::AreConnected(const GraphId& first, const GraphId& second) const {
  //singleton is efficient here but does mean we cant reconfigure the tiles on the fly
  static const connectivity_map_t connectivity_map(this->tile_hierarchy_);

  //both must be the same color but also neither must be 0
  auto first_color = connectivity_map.get_color(first.Tile_Base());
  auto second_color = connectivity_map.get_color(second.Tile_Base());
  return first_color == second_color && first_color != 0;
}

// Get a pointer to a graph tile object given a GraphId.
const GraphTile* GraphReader::GetGraphTile(const GraphId& graphid) {
  //TODO: clear the cache automatically once we become overcommitted by a certain amount

  // Check if the level/tileid combination is in the cache
  auto cached = cache_.find(graphid.Tile_Base());
  if(cached != cache_.end())
    return &cached->second;

  // It wasn't in cache so create a GraphTile object. This reads the tile from disk
  GraphTile tile(tile_hierarchy_, graphid);
  // Need to check that the tile could be loaded, if it has no size it wasn't loaded
  if(tile.size() == 0)
    return nullptr;
  // Keep a copy in the cache and return it
  cache_size_ += tile.size();
  auto inserted = cache_.emplace(graphid.Tile_Base(), std::move(tile));
  return &inserted.first->second;
}

const GraphTile* GraphReader::GetGraphTile(const PointLL& pointll, const uint8_t level){
  return GetGraphTile(tile_hierarchy_.GetGraphId(pointll, level));
}

const GraphTile* GraphReader::GetGraphTile(const PointLL& pointll){
  return GetGraphTile(pointll, tile_hierarchy_.levels().rbegin()->second.level);
}

const TileHierarchy& GraphReader::GetTileHierarchy() const {
  return tile_hierarchy_;
}

/**
 * Clears the cache
 */
void GraphReader::Clear() {
  cache_size_ = 0;
  cache_.clear();
}

/** Returns true if the cache is over committed with respect to the limit
 * @return  true
 */
bool GraphReader::OverCommitted() const {
  return max_cache_size_ < cache_size_;
}

// Convenience method to get an opposing directed edge graph Id.
GraphId GraphReader::GetOpposingEdgeId(const GraphId& edgeid) {
  return GetOpposingEdgeId(edgeid, NO_TILE);
}
GraphId GraphReader::GetOpposingEdgeId(const GraphId& edgeid, const GraphTile*& tile) {
  tile = GetGraphTile(edgeid);
  const auto* directededge = tile->directededge(edgeid);
  GraphId id = directededge->endnode();
  if (directededge->leaves_tile()) {
    // Get tile at the end node
    tile = GetGraphTile(id);
  }
  if (tile != nullptr) {
    id.fields.id = tile->node(id)->edge_index() + directededge->opp_index();
    return id;
  }
  return {};
}

// Convenience method to get an opposing directed edge.
const DirectedEdge* GraphReader::GetOpposingEdge(const GraphId& edgeid) {
  return GetOpposingEdge(edgeid, NO_TILE);
}
const DirectedEdge* GraphReader::GetOpposingEdge(const GraphId& edgeid, const GraphTile*& tile) {
  GraphId oppedgeid = GetOpposingEdgeId(edgeid, tile);
  return oppedgeid.Is_Valid() ? tile->directededge(oppedgeid) : nullptr;
}

// Convenience method to get the relative edge density (from the
// begin node of an edge).
uint32_t GraphReader::GetEdgeDensity(const GraphId& edgeid) {
  // Get the end node of the opposing directed edge
  const DirectedEdge* opp_edge = GetOpposingEdge(edgeid);
  GraphId id = opp_edge->endnode();
  const GraphTile* tile = GetGraphTile(id);
  return (tile != nullptr) ? tile->node(id)->density() : 0;
}


}
}
