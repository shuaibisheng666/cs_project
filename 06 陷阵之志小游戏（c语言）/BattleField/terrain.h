#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <string>

// TerrainType
enum TerrainType {PLAIN, MOUNTAIN, OCEAN};

class Terrain {
public:
    Terrain();

    std::string getSymbol();

private:
    TerrainType ttype;
};

#endif // TERRAIN_H_INCLUDED
