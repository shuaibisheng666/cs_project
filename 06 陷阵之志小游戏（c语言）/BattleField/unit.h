#ifndef UNITS_H_INCLUDED
#define UNITS_H_INCLUDED

#include <string>

/* Type of Units */
enum UnitType {SOLDIER, TANK, };

/* Class for units */
class Unit {
public:
    Unit(UnitType u, bool sd, int row, int col);

    // UnitType information
    std::string getSymbol() const;

    // Get the coordinate of the current unit
    int getRow() const;
    int getCol() const;

    // Set the coordinates
    void setCoord(int row, int col);

    // unit performs move action
    void move(int row, int col);

    // Check which side the unit belongs to
    bool getSide() const;

    // Get movement point, which depends on unit type
    int getMovPoints() const;

private:
    UnitType type;
    bool side;
    int urow, ucol;
};

#endif // UNITS_H_INCLUDED
