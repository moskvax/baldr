#include <string.h>
#include "baldr/graphtileheader.h"
#include "baldr/nodeinfo.h"
#include "baldr/directededge.h"
#include "baldr/edgeinfo.h"
#include "baldr/datetime.h"
#include "config.h"

using namespace valhalla::baldr;

namespace valhalla {
namespace baldr {

// Default constructor.
GraphTileHeader::GraphTileHeader() {
  memset(this, 0, sizeof(GraphTileHeader));
  strncpy(version_, PACKAGE_VERSION, kMaxVersionSize);
  version_[kMaxVersionSize-1] = 0;
}

// Get the GraphId (tileid and level) of this tile.
const GraphId& GraphTileHeader::graphid() const {
  return graphid_;
}

// Set the graph Id of this tile.
void GraphTileHeader::set_graphid(const baldr::GraphId& graphid) {
  graphid_ = graphid;
}

// Get the date created
uint32_t GraphTileHeader::date_created() const {
  return date_created_;
}

// Set the date created
void GraphTileHeader::set_date_created(const uint32_t date) {
  date_created_ = date;
}

// Get the version string.
std::string GraphTileHeader::version() const {
  return version_;
}

// Set the version string.
void GraphTileHeader::set_version(const std::string& version) {
  strncpy(version_, version.c_str(), kMaxVersionSize);
  version_[kMaxVersionSize-1] = 0;
}

// Get the relative road density within this tile.
uint32_t GraphTileHeader::density() const {
  return static_cast<uint32_t>(density_);
}

// Set the relative road density within this tile.
void GraphTileHeader::set_density(const uint32_t density) {
  density_ = density;
}

// Get the relative quality of name assignment for this tile.
uint32_t GraphTileHeader::name_quality() const {
  return static_cast<uint32_t>(name_quality_);
}

// Set the relative quality of name assignment for this tile.
void GraphTileHeader::set_name_quality(const uint32_t name_quality) {
  name_quality_ = name_quality;
}

// Get the relative quality of speed assignment for this tile.
uint32_t GraphTileHeader::speed_quality() const {
  return static_cast<uint32_t>(speed_quality_);
}

// Set the relative quality of speed assignment for this tile.
void GraphTileHeader::set_speed_quality(const uint32_t speed_quality) {
  speed_quality_ = speed_quality;
}

// Get the relative quality of exit signs for this tile.
uint32_t GraphTileHeader::exit_quality() const {
  return static_cast<uint32_t>(exit_quality_);
}

// Set the relative quality of exit signs for this tile.
void GraphTileHeader::set_exit_quality(const uint32_t exit_quality) {
  exit_quality_ = exit_quality;
}

// Get the count of nodes in the tile.
uint32_t GraphTileHeader::nodecount() const {
  return nodecount_;
}

// Sets the number of nodes in this tile.
void GraphTileHeader::set_nodecount(const uint32_t count) {
  nodecount_ = count;
}

// Get the count of directed edges in the tile.
uint32_t GraphTileHeader::directededgecount() const {
  return directededgecount_;
}

// Sets the number of directed edges in this tile.
void GraphTileHeader::set_directededgecount(const uint32_t count) {
  directededgecount_ = count;
}

// Gets the number of signs in the tile.
uint32_t GraphTileHeader::signcount() const {
  return signcount_;
}

// Sets the sign count.
void GraphTileHeader::set_signcount(const uint32_t count) {
  signcount_ = count;
}

// Gets the number of transit departures in this tile.
uint32_t GraphTileHeader::departurecount() const {
  return departurecount_;
}

// Sets the number of transit departures in this tile.
void GraphTileHeader::set_departurecount(const uint32_t departures) {
  departurecount_ = departures;
}

// Gets the number of transit stops in this tile.
uint32_t GraphTileHeader::stopcount() const {
  return stopcount_;
}

// Sets the number of transit stops in this tile.
void GraphTileHeader::set_stopcount(const uint32_t stops) {
  stopcount_ = stops;
}

// Gets the number of transit routes in this tile.
uint32_t GraphTileHeader::routecount() const {
  return routecount_;
}

// Sets the number of transit routes in this tile.
void GraphTileHeader::set_routecount(const uint32_t routes) {
  routecount_ = routes;
}

// Gets the number of transit transfers in this tile.
uint32_t GraphTileHeader::transfercount() const {
  return transfercount_;
}

// Sets the number of transit transfers in this tile.
void GraphTileHeader::set_transfercount(const uint32_t transfers) {
  transfercount_ = transfers;
}

// Gets the number of access restrictions in this tile.
uint32_t GraphTileHeader::access_restriction_count() const {
  return access_restriction_count_;
}

// Sets the number of restrictions in this tile.
void GraphTileHeader::set_access_restriction_count(const uint32_t n) {
  access_restriction_count_ = n;
}

// Gets the number of admins in the tile.
uint32_t GraphTileHeader::admincount() const {
  return admincount_;
}

// Sets the admin count.
void GraphTileHeader::set_admincount(const uint32_t count) {
  admincount_ = count;
}

// Get the offset in bytes to the start of the edge information.
uint32_t GraphTileHeader::edgeinfo_offset() const {
  return edgeinfo_offset_;
}

// Sets the offset to the edge info.
void GraphTileHeader::set_edgeinfo_offset(const uint32_t offset) {
  edgeinfo_offset_ = offset;
}

// Get the offset in bytes to the start of the text / names list.
uint32_t GraphTileHeader::textlist_offset() const {
  return textlist_offset_;
}

// Sets the offset to the text list.
void GraphTileHeader::set_textlist_offset(const uint32_t offset) {
  textlist_offset_ = offset;
}

// Get the offset in bytes to the complex restriction list.
uint32_t GraphTileHeader::complex_restriction_offset() const {
  return complex_restriction_offset_;
}

// Sets the offset to the list of complex restrictions.
void GraphTileHeader::set_complex_restriction_offset(const uint32_t offset) {
  complex_restriction_offset_ = offset;
}

// Sets the edge bin offsets
void GraphTileHeader::set_edge_cell_offsets(const uint32_t (&offsets)[kCellCount]) {
  memcpy(cell_offsets_, offsets, sizeof(cell_offsets_));
}

// Get the offset to the given cell in the 5x5 grid.
std::pair<uint32_t, uint32_t> GraphTileHeader::cell_offset(size_t column, size_t row) const {
  auto i = row * kGridDim + column;
  if(i < kCellCount)
    return std::make_pair(i == 0 ? 0 : cell_offsets_[i - 1], cell_offsets_[i]);
  throw std::runtime_error("Cell out of bounds");
}

}
}
