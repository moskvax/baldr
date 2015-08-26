#include <string.h>
#include "baldr/transitroute.h"

namespace valhalla {
namespace baldr {

// Constructor with arguments
TransitRoute:: TransitRoute(const uint32_t routeid,const char* tl_routeid,
                            const uint32_t long_name_offset, const uint32_t desc_offset)
    : routeid_(routeid),
      long_name_offset_(long_name_offset),
      desc_offset_(desc_offset) {
  strncpy(tl_routeid_, tl_routeid, kOneStopIdSize);
}

// Get the internal route Id.
uint32_t TransitRoute::routeid() const {
  return routeid_;
}

/**
* Get the TransitLand one stop Id for this route.
* @return  Returns the TransitLand one-stop Id.
*/
const char* TransitRoute::tl_routeid() const {
  return tl_routeid_;
}

/**
* Get the text/name offset for the long route name.
* @return  Returns the long name offset in the text/name list.
*/
uint32_t TransitRoute::long_name_offset() const {
  return long_name_offset_;
}

/**
* Get the text/name offset for the route description.
* @return  Returns the description offset in the text/name list.
*/
uint32_t TransitRoute::desc_offset() const {
  return desc_offset_;
}

// operator < - for sorting. Sort by route Id.
bool TransitRoute::operator < (const TransitRoute& other) const {
  return routeid() < other.routeid();
}

}
}
