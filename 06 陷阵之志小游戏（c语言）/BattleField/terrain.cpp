#include <cassert>
#include "terrain.h"

// Constructor
Terrain::Terrain()
  : ttype(PLAIN) {}

std::string Terrain::getSymbol() {
  switch (ttype) {
  case PLAIN:
      return "  ";
  }

  // assert(false);
  return "";
}