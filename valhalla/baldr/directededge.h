#ifndef VALHALLA_BALDR_DIRECTEDEDGE_H_
#define VALHALLA_BALDR_DIRECTEDEDGE_H_

#include <valhalla/baldr/graphid.h>
#include <valhalla/baldr/graphconstants.h>
#include <valhalla/baldr/turn.h>
#include <valhalla/baldr/json.h>

namespace valhalla {
namespace baldr {

/**
 * Directed edge within the graph.
 */
class DirectedEdge {
 public:
  /**
   * Constructor
   */
  DirectedEdge();

  /**
   * Gets the end node of this directed edge.
   * @return  Returns the end node.
   */
  GraphId endnode() const;

  /**
   * Set the end node of this directed edge.
   * @param  endnode  End node of the directed link.
   */
  void set_endnode(const baldr::GraphId& endnode);

  /**
   * Offset to the common edge data. The offset is from the start
   * of the common edge information  within a tile.
   * @return  Returns offset from the start of the edge info within a tile.
   */
  uint64_t edgeinfo_offset() const;

  /**
   * Set the offset to the common edge info. The offset is from the start
   * of the common edge info within a tile.
   * @param  offset  Offset from the start of the edge info within a tile.
   */
  void set_edgeinfo_offset(const uint32_t offset);

  /**
   * General restriction or access condition (per mode) for this directed edge.
   * @return  Returns the restriction for the directed edge.
   */
  uint64_t access_restriction() const;

  /**
   * Set the modes which have access restrictions on this edge.
   * @param  access  Modes with access restrictions.
   */
  void set_access_restriction(const uint32_t access);

  /**
   * Does this directed edge have exit signs?
   * @return  Returns true if the directed edge has exit signs,
   *          false if not.
   */
  bool exitsign() const;

  /**
   * Sets the exit sign flag.
   * @param  exit  True if this directed edge has exit signs, false if not.
   */
  void set_exitsign(const bool exit);

  /**
   * Gets the length of the edge in meters.
   * @return  Returns the length in meters.
   */
  uint32_t length() const;

  /**
   * Sets the length of the edge in meters.
   * @param  length  Length of the edge in meters.
   */
  void set_length(const uint32_t length);

  /**
   * Get the weighted grade factor
   * @return  Returns the weighted grade factor (0-15).
   *          where 0 is a 10% grade and 15 is 15%
   */
  uint32_t weighted_grade() const;

  /**
   * Sets the weighted grade factor (0-15) for the edge.
   * @param  factor  Weighted grade factor.
   */
  void set_weighted_grade(const uint32_t factor);

  /**
   * Get the road curvature factor. TODO
   * @return  Returns the curvature factor (0-15).
   */
  uint32_t curvature() const;

  /**
   * Sets the curvature factor (0-16) for the edge. TODO.
   * @param  factor  Curvature factor.
   */
  void set_curvature(const uint32_t factor);

  /**
   * Is driving on the right hand side of the road along this edge?
   * @return  Returns true if this edge uses right-side driving, false if
   *          left-side driving.
   */
  bool drive_on_right() const;

  /**
   * Set the flag indicating driving is on the right hand side of the road
   * along this edge?
   * @param rsd  True if this edge uses right-side driving, false if
   *             left-side driving.
   */
  void set_drive_on_right(const bool rsd);

  /**
   * Does this edge have a toll or is it part of a toll road?
   * @return  Returns true if this edge is part of a toll road, false if not.
   */
  bool toll() const;

  /**
   * Sets the flag indicating this edge has a toll or is it part of
   * a toll road.
   * @param  toll  True if this edge is part of a toll road, false if not.
   */
  void set_toll(const bool toll);

  /**
   * Does this edge have a seasonal access (e.g., closed in the winter)?
   * @return  Returns true if this edge has seasonal access, false if not.
   */
  bool seasonal() const;

  /**
   * Sets the flag indicating this edge has seasonal access.
   * @param  seasonal  True if this edge has seasonal access, false if not.
   */
  void set_seasonal(const bool seasonal);

  /**
   * Is this edge part of a private or no through road that allows access
   * only if required to get to a destination?
   * @return  Returns true if the edge is destination only / private access.
   */
  bool destonly() const;

  /**
   * Sets the destination only (private) flag. This indicates the edge should
   * allow access only to locations that are destinations and not allow
   * "through" traffic
   * @param  destonly  True if the edge is private (allows access to
   *                   destination only), false if not.
   */
  void set_dest_only(const bool destonly);

  /**
   * Is this edge part of a tunnel?
   * @return  Returns true if this edge is part of a tunnel, false if not.
   */
  bool tunnel() const;

  /**
   * Sets the flag indicating this edge has is a tunnel of part of a tunnel.
   * @param  tunnel   True if the edge is a tunnel, false if not.
   */
  void set_tunnel(const bool tunnel);

  /**
   * Is this edge part of a bridge?
   * @return  Returns true if this edge is part of a bridge, false if not.
   */
  bool bridge() const;

  /**
   * Sets the flag indicating this edge has is a bridge of part of a bridge.
   * @param  bridge   True if the edge is a bridge, false if not.
   */
  void set_bridge(const bool bridge);

  /**
   * Is this edge part of a roundabout?
   * @return  Returns true if this edge is part of a roundabout, false if not.
   */
  bool roundabout() const;

  /**
   * Sets the flag indicating the edge is part of a roundabout.
   * @param  roundabout  True if the edge is part of a roundabout, false if not.
   */
  void set_roundabout(const bool roundabout);

  /**
   * Is this edge is unreachable by driving. This can happen if a driveable
   * edge is surrounded by pedestrian only edges (e.g. in a city center) or
   * is not properly connected to other edges.
   * @return  Returns true if this edge is unreachable by auto.
   */
  bool unreachable() const;

  /**
   * Sets the flag indicating the edge is unreachable by driving. This can
   * happen if a driveable edge is surrounded by pedestrian only edges (e.g.
   * in a city center) or is not properly connected to other edges.
   * @param  unreachable  True if the edge is unreachable by driving,
   *                      false if not.
   */
  void set_unreachable(const bool unreachable);

  /**
   * A traffic signal occurs at the end of this edge.
   * @return  Returns true if a traffic signal is present at the end of the
   *          directed edge.
   */
  bool traffic_signal() const;

  /**
   * Sets the flag indicating a traffic signal is present at the end of
   * this edge.
   * @param  signal  True if a traffic signal exists at the end of this edge,
   *                 false if not.
   */
  void set_traffic_signal(const bool signal);

  /**
   * Is this directed edge stored forward in edgeinfo (true) or
   * reverse (false).
   * @return  Returns true if stored forward, false if reverse.
   */
  bool forward() const;

  /**
   * Set the forward flag. Tells if this directed edge is stored forward
   * in edgeinfo (true) or reverse (false).
   * @param  forward  Forward flag.
   * */
  void set_forward(const bool forward);

  /**
   * Edge leads to a "no thru" region where there are no exits other than
   * the incoming edge. This flag is populated by processing the graph to
   * identify such edges. This is used to speed pedestrian routing.
   * @return  Returns true if the edge leads into a no thru region.
   */
  bool not_thru() const;

  /**
   * Set the not_thru flag. If an edge leads to a "no thru" region where
   * there are no exits other than the incoming edge. This flag is populated
   * by processing the graph toidentify such edges.
   * @param  not_thru True if the edge leads into a no thru region.
   */
  void set_not_thru(const bool not_thru);

  /**
   * Get the index of the opposing directed edge at the end node of this
   * directed edge. Can be used to find the start node of this directed edge.
   * @return  Returns the index of the opposing directed edge at the end node
   *          of this directed edge.
   */
  uint32_t opp_index() const;

  /**
   * Set the index of the opposing directed edge at the end node of this
   * directed edge.
   * @param  opp_index  Opposing directed edge index at the end node.
   * */
  void set_opp_index(const uint32_t opp_index);

  /**
   * Get the cycle lane type along this edge.
   * @returns   Returns the type (if any) of bicycle lane along this edge.
   */
  CycleLane cyclelane() const;

  /**
   * Sets the type of cycle lane (if any) present on this edge.
   * @param  cyclelane   Type of cycle lane.
   */
  void set_cyclelane(const CycleLane cyclelane);

  /**
   * Get the bike network mask for this directed edge.
   * @return  Returns the bike network mask for this directed edge.
   */
  uint32_t bike_network() const;

  /**
   * Sets the bike network mask indicating which (if any) bicycle networks are
   * along this edge. See baldr/directededge.h for definitions.
   * @param  bikenetwork  Bicycle network mask.
   */
  void set_bike_network(const uint32_t bike_network);

  /**
   * Get the truck route flag for this directed edge.
   * @return  Returns true if part of a truck network/route, false otherwise.
   */
  bool truck_route() const;

  /**
   * Set the truck route flag for this directed edge.
   * @param  truck_route  Truck route flag.
   */
  void set_truck_route(const bool truck_route);

  /**
   * Get the number of lanes for this directed edge.
   * @return  Returns the number of lanes for this directed edge.
   */
  uint32_t lanecount() const;

  /**
   * Sets the number of lanes
   * @param  lanecount  Number of lanes
   */
  void set_lanecount(const uint32_t lanecount);

  /**
   * Simple turn restrictions from the end of this directed edge.
   * These are turn restrictions from one edge to another that apply to
   * all vehicles, at all times.
   * @return  Returns a bit mask that indicates the local edge indexes
   *          of outbound directed edges that are restricted.
   */
  uint32_t restrictions() const;

  /**
   * Set simple turn restrictions from the end of this directed edge.
   * These are turn restrictions from one edge to another that apply to
   * all vehicles, at all times.
   * @param  mask A bit mask that indicates the local edge indexes
   *          of outbound directed edges that are restricted.
   */
  void set_restrictions(const uint32_t mask);

  /**
   * Get the specialized use of this edge.
   * @return  Returns the use type of this edge.
   */
  Use use() const;

  /**
   * Sets the specialized use type of this edge.
   * @param  use  Use of this edge.
   */
  void set_use(const Use use);

  /**
   * Is this edge a transit line (bus or rail)?
   * @return  Returns true if this edge is a transit line.
   */
  bool IsTransitLine() const;

  /**
   * Get the speed type (see graphconstants.h)
   * @return  Returns the speed type.
   */
  SpeedType speed_type() const;

  /**
   * Set the speed type (see graphconstants.h)
   * @param  speed_type  Speed type.
   */
  void set_speed_type(const SpeedType speed_type);

  /**
   * Get the country crossing flag.
   * @return  Returns true if the edge crosses into a new country.
   */
  bool ctry_crossing() const;

  /**
   * Set the country crossing flag.
   * @param  crossing  True if this edge crosses into a new country.
   */
  void set_ctry_crossing(const bool crossing);

  /**
   * Get the access modes in the forward direction (bit field).
   * @return  Returns the access modes in the forward direction.
   */
  uint32_t forwardaccess() const;

  /**
   * Set the access modes in the forward direction (bit field).
   * @param  modes  Allowed access modes in the forward direction.
   */
  void set_forwardaccess(const uint32_t modes);

  /**
   * Set all forward access modes to true (used for transition edges)
   */
  void set_all_forward_access();

  /**
   * Get the access modes in the reverse direction (bit field).
   * @return  Returns the access modes in the reverse direction.
   */
  uint32_t reverseaccess() const;

  /**
   * Set the access modes in the reverse direction (bit field).
   * @param  modes  Allowed access modes in the reverse direction.
   */
  void set_reverseaccess(const uint32_t modes);

  /**
   * Gets the speed in KPH.
   * @return  Returns the speed in KPH.
   */
  uint32_t speed() const;

  /**
   * Sets the speed in KPH.
   * @param  speed  Speed in KPH.
   */
  void set_speed(const uint32_t speed);

  /**
   * Gets the truck speed in KPH.
   * @return  Returns the truck speed in KPH.
   */
  uint32_t truck_speed() const;

  /**
   * Sets the truck speed in KPH.
   * @param  truck speed  Speed in KPH.
   */
  void set_truck_speed(const uint32_t speed);

  /**
   * Get the classification (importance) of the road/path.
   * @return  Returns road classification / importance.
   */
  RoadClass classification() const;

  /**
   * Sets the classification (importance) of this edge.
   * @param  roadclass  Road class.
   */
  void set_classification(const RoadClass roadclass);

  /**
   * Is this edge unpaved or bad surface?
   */
  bool unpaved() const;

  /**
   * Get the surface type (see graphconstants.h). This is a general indication
   * of smoothness.
   */
  Surface surface() const;

  /**
   * Sets the surface type (see baldr/graphconstants.h). This is a general
   * indication of smoothness.
   * @param  surface   Surface type.
   */
  void set_surface(const Surface surface);

  /**
   * Is this edge a link/ramp?
   */
  bool link() const;

  /**
   * Sets the link flag indicating the edge is part of a link or connection
   * (ramp or turn channel).
   * @param  link  True if the edge is part of a link.
   */
  void set_link(const bool link);

  /**
   * Gets the intersection internal flag. This indicates the edge is "internal"
   * to an intersection. This is derived from OSM based on geometry of an
   * of nearby edges and is used for routing behavior on doubly digitized
   * intersections.
   * @return  Returns true if the edge is internal to an intersection.
   */
  bool internal() const;

  /**
   * Sets the intersection internal flag indicating the edge is "internal"
   * to an intersection. This is derived from OSM based on geometry of an
   * of nearby edges and is used for routing behavior on doubly digitized
   * intersections.
   * @param  internal  True if the edge is internal to an intersection.
   */
  void set_internal(const bool internal);

  /**
   * Gets the turn type given the prior edge's local index
   * (index of the inbound edge).
   * @param  localidx  Local index at the node of the inbound edge.
   * @return  Returns the turn type (see turn.h)
   */
  Turn::Type turntype(const uint32_t localidx) const;

  /**
   * Sets the turn type given the prior edge's local index
   * (index of the inbound edge).
   * @param  localidx  Local index at the node of the inbound edge.
   * @param  turntype  Turn type (see TODO)
   */
  void set_turntype(const uint32_t localidx, const Turn::Type turntype);

  /**
   * Is there an edge to the left, in between the from edge and this edge.
   * @param localidx  Local index at the node of the inbound edge.
   * @return  Returns true if there is an edge to the left, false if not.
   */
  bool edge_to_left(const uint32_t localidx) const;

  /**
   * Set the flag indicating there is an edge to the left, in between
   * the from edge and this edge.
   * @param  localidx  Local index at the node of the inbound edge.
   * @param  left      True if there is an edge to the left, false if not.
   */
  void set_edge_to_left(const uint32_t localidx, const bool left);

  /**
   * Get the stop impact when transitioning from the prior edge (given
   * by the local index of the corresponding inbound edge at the node).
   * @param  localidx  Local index at the node of the inbound edge.
   * @return  Returns the relative stop impact from low (0) to high (7).
   */
  uint32_t stopimpact(const uint32_t localidx) const;

  /**
   * Set the stop impact when transitioning from the prior edge (given
   * by the local index of the corresponding inbound edge at the node).
   * @param  localidx    Local index at the node of the inbound edge.
   * @param  stopimpact  Relative stop impact from low (0) to high (7).
   */
  void set_stopimpact(const uint32_t localidx, const uint32_t stopimpact);

  /**
   * Get the transit line Id (for departure lookups along an edge)
   * @return  Returns the transit line Id.
   */
  uint32_t lineid() const;

  /**
   * Set the unique transit line Id.
   * @param  lineid  Line Id indicating a unique stop-pair and route.
   */
  void set_lineid(const uint32_t lineid);

  /**
   * Is there an edge to the right, in between the from edge and this edge.
   * @param localidx  Local index at the node of the inbound edge.
   * @return  Returns true if there is an edge to the right, false if not.
   */
  bool edge_to_right(const uint32_t localidx) const;

  /**
   * Set the flag indicating there is an edge to the right, in between
   * the from edge and this edge.
   * @param  localidx  Local index at the node of the inbound edge.
   * @param  right     True if there is an edge to the right, false if not.
   */
  void set_edge_to_right(const uint32_t localidx, const bool right);

  /**
   * Get the index of the directed edge on the local level of the graph
   * hierarchy. This is used for turn restrictions so the edges can be
   * identified on the different levels.
   * @return  Returns the index of the edge on the local level.
   */
  uint32_t localedgeidx() const;

  /** Set the index of the directed edge on the local level of the graph
   * hierarchy. This is used for turn restrictions so the edges can be
   * identified on the different levels.
   * @param idx The index of the edge on the local level.
   */
  void set_localedgeidx(const uint32_t idx);

  /**
   * Get the index of the opposing directed edge on the local hierarchy level
   * at the end node of this directed edge. Only stored for the first 8 edges
   * so it can be used for edge transition costing.
   * @return  Returns the index of the opposing directed edge on the local
   *          hierarchy level at end node of this directed edge.
   */
  uint32_t opp_local_idx() const;

  /**
   * Set the index of the opposing directed edge on the local hierarchy level
   * at the end node of this directed edge. Only stored for the first 8 edges
   * so it can be used for edge transition costing.
   * @param localidx  The index of the opposing directed edge on the local
   *                  hierarchy level at end node of this directed edge.
   */
  void set_opp_local_idx(const uint32_t localidx);

  /**
   * Indicates the mask of the superseded edge bypassed by a shortcut.
   * Shortcuts bypass nodes that only connect to lower levels in the hierarchy
   * (other than the 1-2 higher level edges that superseded by the shortcut).
   * @return  Returns the shortcut mask of the matching superseded edge
   *          outbound from the node. 0 indicates the edge is not a shortcut.
   */
  uint32_t shortcut() const;

  /**
   * Set the mask for whether this edge represents a shortcut between 2 nodes.
   * Shortcuts bypass nodes that only connect to lower levels in the hierarchy
   * (other than the 1-2 higher level edges that superseded by the shortcut).
   * @param  shortcut  Mask indicating the edge that is superseded by
   *                   the shortcut. 0 if not a shortcut.
   */
  void set_shortcut(const uint32_t shortcut);

  /**
   * Mask indicating the shortcut that supersedes this directed edge.
   * Superseded edges can be skipped unless downward transitions are allowed.
   * @return  Returns the mask of the matching shortcut edge that supersedes this
   *          directed edge outbound from the node. 0 indicates the edge is not
   *          superseded by a shortcut edge.
   */
  uint32_t superseded() const;

  /**
   * Set the mask for whether this edge is superseded by a shortcut edge.
   * Superseded edges can be skipped unless downward transitions are allowed.
   * @param  superseded  Mask that matches the shortcut that supersedes this
   *                     directed edge. 0 if not superseded by a shortcut.
   */
  void set_superseded(const uint32_t superseded);

  /**
   * Does this edge represent a transition up one level in the hierarchy.
   * Transition edges move between nodes in different levels of the
   * hierarchy but have no length or other attribution. An upward transition
   * is a transition from a minor road hierarchy (local) to more major
   * (arterial).
   * @return  Returns true if the edge is a transition from a lower level
   *          to a higher (false if not).
   */
  bool trans_up() const;

  /**
   * Set the flag for whether this edge represents a transition up one level
   * in the hierarchy. Transition edges move between nodes in different levels
   * of the hierarchy but have no length or other attribution. An upward
   * transition is a transition from a minor road hierarchy (local) to more
   * major (arterial).
   * @param  trans_up  True if the edge is a transition from a lower level
   *          to a higher (false if not).
   */
  void set_trans_up(const bool trans_up);

  /**
   * Does this edge represent a transition down one level in the hierarchy.
   * Transition edges move between nodes in different levels of the
   * hierarchy but have no length or other attribution. An downward transition
   * is a transition from a major road hierarchy (highway) to more minor
   * (arterial).
   * @return  Returns true if the edge is a transition from an upper level
   *          to a lower (false if not).
   */
  bool trans_down() const;

  /**
   * Set the flag for whether this edge represents a transition down one level
   * in the hierarchy. Transition edges move between nodes in different levels
   * of the hierarchy but have no length or other attribution. A downward
   * transition is a transition from a major road hierarchy (highway) to more
   * minor (arterial).
   * @param   trans_down  True if the edge is a transition from an upper level
   *          to a lower (false if not).
   */
  void set_trans_down(const bool trans_down);

  /**
   * Is this edge a shortcut edge. If there are more than kMaxShortcutsFromNode
   * shortcuts no mask is set but this flag is set to true.
   * @return  Returns true if this edge is a shortcut.
   */
  bool is_shortcut() const;

  /**
   * Does this directed edge end in a different tile.
   * @return  Returns true if the end node of this directed edge
   *          is in a different tile.
   */
  bool leaves_tile() const;

  /**
   * Set the flag indicating whether the end node of this directed edge is in
   * a different tile
   * @param  leaves_tile  True if the end node of this edge is in a different
   *                      tile than the start node (and the directed edge
   *                      itself).
   */
  void set_leaves_tile(const bool leaves_tile);

  /**
   * Create a json object representing this edge
   * @return  Returns the json object
   */
  json::MapPtr json() const;

 protected:
  // End node
  GraphId endnode_;

  // Data offsets and flags for extended data. Where a flag exists the actual
  // data can be indexed by the directed edge Id within the tile.
  uint64_t edgeinfo_offset_           : 25; // Offset to edge data.
  uint64_t access_restriction_        : 12; // General restriction or access
                                            // condition (per mode)
  uint64_t start_complex_restriction_ : 12; // Complex restriction (per mode)
                                            // starts on this directed edge
  uint64_t end_complex_restriction_   : 12; // Complex restriction (per mode)
                                            // ends on this directed edge
  uint64_t exitsign_                  : 1;  // Exit signs exist for this edge
  uint64_t spare1_                    : 2;

  // Attributes. Can be used in edge costing methods to favor or avoid edges.
  // Speed values above 250 used for special cases (closures, construction)
  uint64_t speed_          : 8; // Speed (kph)
  uint64_t truck_speed_    : 8; // Truck speed (kph)
  uint64_t restrictions_   : 8; // Restrictions - mask of local edge indexes
                                // at the end node that are restricted.
  uint64_t lanecount_      : 4; // Number of lanes
  uint64_t bike_network_   : 4; // Edge that is part of a bicycle network
  uint64_t use_            : 6; // Specific use types
  uint64_t speed_type_     : 2; // Speed type (tagged vs. categorized)
  uint64_t opp_index_      : 7; // Opposing directed edge index
  uint64_t drive_on_right_ : 1; // Driving side. Right if true (false=left)
  uint64_t spare2_         : 1;
  uint64_t spare3_         : 1;
  uint64_t toll_           : 1; // Edge is part of a toll road.
  uint64_t seasonal_       : 1; // Seasonal access (ex. no access in winter)
  uint64_t dest_only_      : 1; // Access allowed to destination only
                                //  (private or no through traffic)
  uint64_t tunnel_         : 1; // Is this edge part of a tunnel
  uint64_t bridge_         : 1; // Is this edge part of a bridge?
  uint64_t roundabout_     : 1; // Edge is part of a roundabout
  uint64_t unreachable_    : 1; // Edge that is unreachable by driving
  uint64_t traffic_signal_ : 1; // Traffic signal at end of the directed edge
  uint64_t forward_        : 1; // Is the edge info forward or reverse
  uint64_t not_thru_       : 1; // Edge leads to "no-through" region
  uint64_t cycle_lane_     : 2; // Does this edge have bicycle lanes?
  uint64_t truck_route_    : 1; // Edge that is part of a truck route/network
  uint64_t ctry_crossing_  : 1; // Does the edge cross into new country

  // Legal access to the directed link (also include reverse direction access).
  // See graphconstants.h.
  uint64_t forwardaccess_  : 12;
  uint64_t reverseaccess_  : 12;
  uint64_t classification_ : 3;  // Classification/importance of the road/path
  uint64_t surface_        : 3;  // representation of smoothness
  uint64_t link_           : 1;  // *link tag - Ramp or turn channel
  uint64_t internal_       : 1;  // Edge that is internal to an intersection
  uint64_t spare1          : 32;

  // Geometric attributes: length, weighted grade, curvature factor.
  // Turn types between edges.
  uint64_t turntype_        : 24;   // Turn type (see graphconstants.h)
  uint64_t edge_to_left_    :  8;   // Is there an edge to the left (between
                                    // the "from edge" and this edge)
  uint64_t length_          : 24;   // Length in meters
  uint64_t weighted_grade_  :  4;   // Weighted estimate of grade
  uint64_t curvature_       :  4;   // Curvature factor

  // Stop impact among edges
  struct StopImpact {
    uint32_t stopimpact      : 24; // Stop impact between edges
    uint32_t edge_to_right   :  8; // Is there an edge to the right (between
                                   // "from edge" and this edge)
  };

  // Store either the stop impact or the transit line identifier. Since
  // transit lines are schedule based they have no need for edge transition
  // logic so we can safely share this field.
  union StopOrLine {
    StopImpact s;
    uint32_t   lineid;
  };
  StopOrLine stopimpact_;

  // Hierarchy transitions and shortcut information
  uint32_t localedgeidx_  : 7;  // Index of the edge on the local level
  uint32_t opp_local_idx_ : 7;  // Opposing local edge index (for costing
                                // and Uturn detection)
  uint32_t shortcut_      : 7;  // Shortcut edge (mask)
  uint32_t superseded_    : 7;  // Edge is superseded by a shortcut (mask)
  uint32_t trans_up_      : 1;  // Edge represents a transition up one
                                // level in the hierarchy
  uint32_t trans_down_    : 1;  // Transition down one level
  uint32_t is_shortcut_   : 1;  // True if this edge is a shortcut.
  uint32_t leaves_tile_   : 1;  // True if the end node of this directed edge
                                // is in a different tile.
};

}
}

#endif  // VALHALLA_BALDR_DIRECTEDEDGE_H_
