#ifndef VALHALLA_BALDR_GRAPHTILEHEADER_H_
#define VALHALLA_BALDR_GRAPHTILEHEADER_H_

#include <cstdlib>
#include <string>

#include <valhalla/baldr/graphid.h>

namespace valhalla {
namespace baldr {

// Maximum size of the version string (stored as a fixed size
// character array so the GraphTileHeader size remains fixed).
constexpr size_t kMaxVersionSize = 16;

// Total number of binned edge cells in the tile
constexpr size_t kGridDim = 5;
constexpr size_t kCellCount = kGridDim * kGridDim;

/**
 * Summary information about the graph tile. Includes version
 * information and offsets to the various types of data.
 */
class GraphTileHeader {
 public:
  /**
   * Constructor
   */
  GraphTileHeader();

  /**
   * Get the GraphId (tileid and level) of this tile.
   * @return  Returns the graph Id.
   */
  const baldr::GraphId& graphid() const;

  /**
   * Set the graph Id of this tile.
   * @param  graphid  GraphId (tileid and level) of this tile.
   */
  void set_graphid(const baldr::GraphId& graphid);

  /**
   * Gets the date when this tile was created. Days since pivot date.
   * @return  Returns the date this tile was created.
   */
  uint32_t date_created() const;

  /**
   * Set the date created.
   * @param  date  Days since pivot date.
   */
  void set_date_created(const uint32_t date);

  /**
   * Gets the version of this tile.
   * @return  Returns the version of this tile.
   */
  std::string version() const;

  /**
   * Set the version string.
   * @param  version Version string.
   */
  void set_version(const std::string& version);

  /**
   * Get the relative road density within this tile.
   * @return  Returns the relative density for this tile (0-15).
   */
  uint32_t density() const;

  /**
   * Set the relative road density within this tile.
   * @param  density  Relative road density within this tile (0-15).
   */
  void set_density(const uint32_t density);

  /**
   * Get the relative quality of name assignment for this tile.
   * @return  Returns relative name quality for this tile (0-15).
   */
  uint32_t name_quality() const;

  /**
   * Set the relative quality of name assignment for this tile.
   * @param   name_quality  Relative name quality for this tile (0-15).
   */
  void set_name_quality(const uint32_t name_quality);

  /**
   * Get the relative quality of speed assignment for this tile.
   * @return  Returns relative speed quality for this tile (0-15).
   */
  uint32_t speed_quality() const;

  /**
   * Set the relative quality of speed assignment for this tile.
   * @param  speed_quality   Relative speed quality for this tile (0-15).
   */
  void set_speed_quality(const uint32_t speed_quality);

  /**
   * Get the relative quality of exit signs for this tile.
   * @return  Returns relative exit sign quality for this tile (0-15).
   */
  uint32_t exit_quality() const;

  /**
   * Set the relative quality of exit signs for this tile.
   * @param  exit_quality   Relative exit sign quality for this tile (0-15).
   */
  void set_exit_quality(const uint32_t exit_quality);

  /**
   * Gets the number of nodes in this tile.
   * @return  Returns the number of nodes.
   */
  uint32_t nodecount() const;

  /**
   * Sets the number of nodes in this tile.
   * @param  count  Number of nodes within the tile.
   */
  void set_nodecount(const uint32_t count);

  /**
   * Gets the number of directed edges in this tile.
   * @return  Returns the number of directed edges.
   */
  uint32_t directededgecount() const;

  /**
   * Sets the number of directed edges in this tile.
   * @param  count  Number of directed edges within the tile.
   */
  void set_directededgecount(const uint32_t count);

  /**
   * Gets the number of signs in this tile.
   * @return  Returns the number of signs.
   */
  uint32_t signcount() const;

  /**
   * Sets the number of signs within this tile.
   * @param count Number of signs within the tile.
   */
  void set_signcount(const uint32_t count);

  /**
   * Gets the number of transit departures in this tile.
   * @return  Returns the number of transit departures.
   */
  uint32_t departurecount() const;

  /**
   * Sets the number of transit departures in this tile.
   * @param departures  The number of transit departures.
   */
  void set_departurecount(const uint32_t departures);

  /**
   * Gets the number of transit stops in this tile.
   * @return  Returns the number of transit stops.
   */
  uint32_t stopcount() const;

  /**
   * Sets the number of transit stops in this tile.
   * @param  stops  The number of transit stops.
   */
  void set_stopcount(const uint32_t stops);

  /**
   * Gets the number of transit routes in this tile.
   * @return  Returns the number of transit routes.
   */
  uint32_t routecount() const;

  /**
   * Sets the number of transit routes in this tile.
   * @param  routes  The number of transit routes.
   */
  void set_routecount(const uint32_t routes);

  /**
   * Gets the number of transit transfers in this tile.
   * @return  Returns the number of transit transfers.
   */
  uint32_t transfercount() const;

  /**
   * Sets the number of transit transfers in this tile.
   * @param  transfers   The number of transit transfers.
   */
  void set_transfercount(const uint32_t transfers);

  /**
   * Gets the number of access restrictions in this tile.
   * @return  Returns the number of restrictions.
   */
  uint32_t access_restriction_count() const;

  /**
   * Sets the number of access restrictions in this tile.
   * @param  restrictions   The number of access restrictions.
   */
  void set_access_restriction_count(const uint32_t restrictions);

  /**
   * Gets the number of admin records in this tile.
   * @return  Returns the number of admin records.
   */
  uint32_t admincount() const;

  /**
   * Sets the number of admin records within this tile.
   * @param count Number of admin records within the tile.
   */
  void set_admincount(const uint32_t count);

  /**
   * Gets the offset to the edge info.
   * @return  Returns the number of bytes to offset to the edge information.
   */
  uint32_t edgeinfo_offset() const;

  /**
   * Sets the offset to the edge info.
   * @param offset Offset in bytes to the start of the edge information.
   */
  void set_edgeinfo_offset(const uint32_t offset);

  /**
   * Gets the offset to the text list.
   * @return  Returns the number of bytes to offset to the text list.
   */
  uint32_t textlist_offset() const;

  /**
   * Sets the offset to the text list.
   * @param offset Offset in bytes to the start of the text list.
   */
  void set_textlist_offset(const uint32_t offset);

  /**
   * Get the offset to the administrative information.
   * @return  Returns the number of bytes to offset to the administrative
   *          information.
   */
  uint32_t admininfo_offset() const;

  /**
   * Get the offset to the Complex Restriction list.
   * @return  Returns the number of bytes to offset to the the list of
   *          complex restrictions.
   */
  uint32_t complex_restriction_offset() const;

  /**
   * Sets the offset to the list of complex restrictions.
   * @param offset Offset in bytes to the start of the complex restriction
   *               list.
   */
  void set_complex_restriction_offset(const uint32_t offset);

  /**
   * Get the offset to the given cell in the 5x5 grid, the cells contain
   * graphids for all the edges that intersect the cell
   * @param  column of the grid
   * @param  row of the grid
   * @return the begin and end offset in the list of edge ids
   */
  std::pair<uint32_t, uint32_t> cell_offset(size_t column, size_t row) const;

  /**
   * Sets the edge cell offsets
   * @param the offsets
   */
  void set_edge_cell_offsets(const uint32_t (&offsets)[baldr::kCellCount]);

 protected:
  // GraphId (tileid and level) of this tile
  GraphId graphid_;

  // baldr version.
  char version_[kMaxVersionSize];

  // Quality metrics. These are 4 bit (0-15) relative quality indicators.
  uint64_t density_       : 4;
  uint64_t name_quality_  : 4;
  uint64_t speed_quality_ : 4;
  uint64_t exit_quality_  : 4;
  uint64_t spare1_        : 48;

  // Number of transit departure records
  uint64_t departurecount_ : 24;
  uint64_t stopcount_      : 16;
  uint64_t routecount_     : 12;
  uint64_t transfercount_  : 12;

  // Date the tile was created. Days since pivot date.
  uint32_t date_created_;

  // Record counts (for fixed size records)
  uint32_t nodecount_;                  // Number of nodes
  uint32_t directededgecount_;          // Number of directed edges
  uint32_t signcount_;                  // Number of signs
  uint32_t access_restriction_count_;   // Number of access restriction records
  uint32_t admincount_;                 // Number of admin records

  // Offsets to beginning of data (for variable size records)
  uint32_t edgeinfo_offset_;            // Offset to edge info
  uint32_t textlist_offset_;            // Offset to text list
  uint32_t complex_restriction_offset_; // Offset to complex restriction list

  // Offsets for each cell of the 5x5 grid (for search/lookup)
  uint32_t cell_offsets_[kCellCount];
};

}
}

#endif  // VALHALLA_BALDR_GRAPHTILEHEADER_H_
