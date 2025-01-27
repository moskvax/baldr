#include "baldr/nodeinfo.h"
#include <boost/functional/hash.hpp>
#include <cmath>
#include <valhalla/midgard/logging.h>

#include <baldr/datetime.h>
#include <baldr/graphtile.h>

using namespace valhalla::baldr;

namespace {

const uint32_t ContinuityLookup[] = {0, 7, 13, 18, 22, 25, 27};

json::MapPtr access_json(uint16_t access) {
  return json::map({
    {"bicycle", static_cast<bool>(access && kBicycleAccess)},
    {"bus", static_cast<bool>(access && kBusAccess)},
    {"car", static_cast<bool>(access && kAutoAccess)},
    {"emergency", static_cast<bool>(access && kEmergencyAccess)},
    {"HOV", static_cast<bool>(access && kHOVAccess)},
    {"pedestrian", static_cast<bool>(access && kPedestrianAccess)},
    {"taxi", static_cast<bool>(access && kTaxiAccess)},
    {"truck", static_cast<bool>(access && kTruckAccess)},
  });
}

json::MapPtr admin_json(const AdminInfo& admin, uint16_t tz_index) {
  //admin
  auto m = json::map({
    {"iso_3166-1", admin.country_iso()},
    {"country", admin.country_text()},
    {"iso_3166-2", admin.state_iso()},
    {"state", admin.state_text()},
  });

  //timezone
  const auto& tz_db = DateTime::get_tz_db();
  auto tz = DateTime::get_tz_db().from_index(tz_index);
  if(tz) {
    //TODO: so much to do but posix tz has pretty much all the info
    m->emplace("time_zone_posix", tz->to_posix_string());
    m->emplace("standard_time_zone_name", tz->std_zone_name());
    if(tz->has_dst())
      m->emplace("daylight_savings_time_zone_name", tz->dst_zone_name());
  }

  return m;
}

/**
 * Get the updated bit field.
 * @param dst  Data member to be updated.
 * @param src  Value to be updated.
 * @param pos  Position (pos element within the bit field).
 * @param len  Length of each element within the bit field.
 * @return  Returns an updated value for the bit field.
 */
uint32_t OverwriteBits(const uint32_t dst, const uint32_t src,
                       const uint32_t pos, const uint32_t len) {
  uint32_t shift = (pos * len);
  uint32_t mask  = (((uint32_t)1 << len) - 1) << shift;
  return (dst & ~mask) | (src << shift);
}

}

namespace valhalla {
namespace baldr {

// Default constructor. Initialize to all 0's.
NodeInfo::NodeInfo() {
  memset(this, 0, sizeof(NodeInfo));
}

NodeInfo::NodeInfo(const std::pair<float, float>& ll,
                   const RoadClass rc, const uint32_t access,
                   const NodeType type, const bool traffic_signal) {
  memset(this, 0, sizeof(NodeInfo));
  set_latlng(ll);
  set_bestrc(rc);
  set_access(access);
  set_type(type);
  set_traffic_signal(traffic_signal);
}

// Get the latitude, longitude
const PointLL& NodeInfo::latlng() const {
  return static_cast<const PointLL&>(latlng_);
}

// Sets the latitude and longitude.
void NodeInfo::set_latlng(const std::pair<float, float>& ll) {
  latlng_ = ll;
}

// Get the index in this tile of the first outbound directed edge
uint32_t NodeInfo::edge_index() const {
  return edge_index_;
}

// Set the index in the node's tile of its first outbound edge.
void NodeInfo::set_edge_index(const uint32_t edge_index) {
  if (edge_index > kMaxTileEdgeCount) {
    // Consider this a catastrophic error
    throw std::runtime_error("NodeInfo: edge index exceeds max");
  }
  edge_index_ = edge_index;
}

// Get the number of outbound edges from this node.
uint32_t NodeInfo::edge_count() const {
  return edge_count_;
}

// Set the number of outbound directed edges.
void NodeInfo::set_edge_count(const uint32_t edge_count) {
  if (edge_count > kMaxEdgesPerNode) {
    // Log an error and set count to max.
    LOG_ERROR("NodeInfo: edge count exceeds max: " +
              std::to_string(edge_count));
    edge_count_ = kMaxEdgesPerNode;
  } else {
    edge_count_ = edge_count;
  }
}

// Get the best road class of any outbound edges.
RoadClass NodeInfo::bestrc() const {
  return static_cast<RoadClass>(bestrc_);
}

// Set the best road class of the outbound directed edges.
void NodeInfo::set_bestrc(const RoadClass bestrc) {
   bestrc_ = static_cast<uint32_t>(bestrc);
}

// Get the access modes (bit mask) allowed to pass through the node.
// See graphconstants.h
uint16_t NodeInfo::access() const {
  return access_;
}

// Set the access modes (bit mask) allowed to pass through the node.
void NodeInfo::set_access(const uint32_t access) {
  access_ = access;
}

// Get the intersection type.
IntersectionType NodeInfo::intersection() const {
  return static_cast<IntersectionType>(intersection_);
}

// Set the intersection type.
void NodeInfo::set_intersection(const IntersectionType type) {
  intersection_ = static_cast<uint32_t>(type);
}

// Get the index of the administrative information within this tile.
uint32_t NodeInfo::admin_index() const {
  return admin_index_;
}

// Set the index of the administrative information within this tile.
void NodeInfo::set_admin_index(const uint16_t admin_index) {
  if (admin_index > kMaxAdminsPerTile) {
    // Log an error and set count to max.
    LOG_ERROR("NodeInfo: admin index exceeds max: " +
              std::to_string(admin_index));
    admin_index_ = kMaxAdminsPerTile;
  } else {
    admin_index_ = admin_index;
  }
}

// Returns the timezone index.
uint32_t NodeInfo::timezone() const {
  return timezone_;
}

// Set the timezone index.
void NodeInfo::set_timezone(const uint32_t timezone) {
  if (timezone > kMaxTimeZonesPerTile) {
    // Log an error and set count to max.
    LOG_ERROR("NodeInfo: timezone index exceeds max: " +
              std::to_string(timezone));
    timezone_ = kMaxTimeZonesPerTile;
  } else {
    timezone_ = timezone;
  }
}

// Get the driveability of the local directed edge given a local
// edge index.
Traversability NodeInfo::local_driveability(const uint32_t localidx) const {
  uint32_t s = localidx * 2;     // 2 bits per index
  return static_cast<Traversability>((local_driveability_ & (3 << s)) >> s);
}

// Set the driveability of the local directed edge given a local
// edge index.
void NodeInfo::set_local_driveability(const uint32_t localidx,
                                             const Traversability t) {
  if (localidx > kMaxLocalEdgeIndex) {
    LOG_WARN("Exceeding max local index on set_local_driveability - skip");
  } else {
    local_driveability_ = OverwriteBits(local_driveability_,
                 static_cast<uint32_t>(t), localidx, 2);
  }
}

// Get the relative density at the node.
uint32_t NodeInfo::density() const {
  return density_;
}

// Set the relative density
void NodeInfo::set_density(const uint32_t density) {
  if (density > kMaxDensity) {
    LOG_WARN("Exceeding max. density: " + std::to_string(density));
    density_ = kMaxDensity;
  } else {
    density_ = density;
  }
}

// Gets the node type. See graphconstants.h for the list of types.
NodeType NodeInfo::type() const {
  return static_cast<NodeType>(type_);
}

// Set the node type.
void NodeInfo::set_type(const NodeType type) {
  type_ = static_cast<uint32_t>(type);
}

// Checks if this node is a transit node.
bool NodeInfo::is_transit() const {
  NodeType nt = type();
  return (nt == NodeType::kRailStop || nt == NodeType::kBusStop ||
          nt == NodeType::kMultiUseTransitStop);
}

// Get the number of edges on the local level. We add 1 to allow up to
// up to kMaxLocalEdgeIndex + 1.
uint32_t NodeInfo::local_edge_count() const {
  return local_edge_count_ + 1;
}

// Set the number of driveable edges on the local level. Subtract 1 so
// a value up to kMaxLocalEdgeIndex+1 can be stored.
void NodeInfo::set_local_edge_count(const uint32_t n) {
  if (n > kMaxLocalEdgeIndex+1) {
    LOG_INFO("Exceeding max. local edge count: " + std::to_string(n));
    local_edge_count_ = kMaxLocalEdgeIndex;
  } else if (n == 0) {
    LOG_ERROR("Node with 0 local edges found");
  } else {
    local_edge_count_ = n - 1;
  }
}

// Is this a parent node (e.g. a parent transit stop).
bool NodeInfo::parent() const {
  return parent_;
}

// Set the parent node flag (e.g. a parent transit stop).
void NodeInfo::set_parent(const bool parent) {
  parent_ = parent;
}

// Is this a child node (e.g. a child transit stop).
bool NodeInfo::child() const {
  return child_;
}

// Set the child node flag (e.g. a child transit stop).
void NodeInfo::set_child(const bool child) {
  child_ = child;
}

// Is a mode change allowed at this node? The access data tells which
// modes are allowed at the node. Examples include transit stops, bike
// share locations, and parking locations.
bool NodeInfo::mode_change() const {
  return mode_change_;
}

// Sets the flag indicating a mode change is allowed at this node.
// The access data tells which modes are allowed at the node. Examples
// include transit stops, bike share locations, and parking locations.
void NodeInfo::set_mode_change(const bool mc) {
  mode_change_ = mc;
}

// Is there a traffic signal at this node?
bool NodeInfo::traffic_signal() const {
  return traffic_signal_;
}

// Set the traffic signal flag.
void NodeInfo::set_traffic_signal(const bool traffic_signal) {
  traffic_signal_ = traffic_signal;
}

// Gets the transit stop index. This is used for schedule lookups
// and possibly queries to a transit service.
uint32_t NodeInfo::stop_index() const {
  return stop_.stop_index;
}

// Set the transit stop index.
void NodeInfo::set_stop_index(const uint32_t stop_index) {
  stop_.stop_index = stop_index;
}

// Get the name consistency between a pair of local edges. This is limited
// to the first kMaxLocalEdgeIndex local edge indexes.
bool NodeInfo::name_consistency(const uint32_t from, const uint32_t to) const {
  if (from == to) {
    return true;
  } else if (from < to) {
    return (to > kMaxLocalEdgeIndex) ? false :
        (stop_.name_consistency & 1 << (ContinuityLookup[from] + (to-from-1)));
  } else {
    return (from > kMaxLocalEdgeIndex) ? false :
        (stop_.name_consistency & 1 << (ContinuityLookup[to] + (from-to-1)));
  }
}

/**
 * Set the name consistency between a pair of local edges. This is limited
 * to the first 8 local edge indexes.
 * @param  from  Local index of the from edge.
 * @param  to    Local index of the to edge.
 * @param  c     Are names consistent between the 2 edges?
 */
void NodeInfo::set_name_consistency(const uint32_t from,
                                           const uint32_t to,
                                           const bool c) {
  if (from == to) {
    return;
  } else if (from > kMaxLocalEdgeIndex || to > kMaxLocalEdgeIndex) {
    LOG_WARN("Local index exceeds max in set_name_consistency, skip");
  } else {
    if (from < to) {
      stop_.name_consistency = OverwriteBits(stop_.name_consistency, c,
                   (ContinuityLookup[from] + (to-from-1)), 1);
    } else {
      stop_.name_consistency = OverwriteBits(stop_.name_consistency, c,
                   (ContinuityLookup[to] + (from-to-1)), 1);
    }
  }
}

// Get the heading of the local edge given its local index. Supports
// up to 8 local edges. Headings are expanded from 8 bits.
uint32_t NodeInfo::heading(const uint32_t localidx) const {
  // Make sure everything is 64 bit!
  uint64_t shift = localidx * 8;     // 8 bits per index
  return static_cast<uint32_t>(std::round(
      ((headings_ & (static_cast<uint64_t>(255) << shift)) >> shift)
          * kHeadingExpandFactor));
}

// Set the heading of the local edge given its local index. Supports
// up to 8 local edges. Headings are reduced to 8 bits.
void NodeInfo::set_heading(uint32_t localidx, uint32_t heading) {
  if (localidx > kMaxLocalEdgeIndex) {
    LOG_WARN("Local index exceeds max in set_heading, skip");
  } else {
    // Has to be 64 bit!
    uint64_t hdg = static_cast<uint64_t>(std::round(
        (heading % 360) * kHeadingShrinkFactor));
    headings_ |= hdg << static_cast<uint64_t>(localidx * 8);
  }
}

json::MapPtr NodeInfo::json(const GraphTile* tile) const {
  auto m = json::map({
    {"lon", json::fp_t{latlng_.first, 6}},
    {"lat", json::fp_t{latlng_.second, 6}},
    {"best_road_class", to_string(static_cast<RoadClass>(bestrc_))},
    {"edge_count", static_cast<uint64_t>(edge_count_)},
    {"access", access_json(access_)},
    {"intersection_type", to_string(static_cast<IntersectionType>(intersection_))},
    {"administrative", admin_json(tile->admininfo(admin_index_), timezone_)},
    {"child", static_cast<uint64_t>(child_)},
    {"density", static_cast<uint64_t>(density_)},
    {"local_edge_count", static_cast<uint64_t>(local_edge_count_ + 1)},
    {"mode_change", static_cast<bool>(mode_change_)},
    {"parent", static_cast<bool>(parent_)},
    {"traffic_signal", static_cast<bool>(traffic_signal_)},
    {"type", to_string(static_cast<NodeType>(type_))},
  });
  if(is_transit())
    m->emplace("stop_index", static_cast<uint64_t>(stop_.stop_index));
  return m;
}


}
}
