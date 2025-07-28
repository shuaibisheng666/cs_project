#include <iomanip>
#include "engine.h"
#include "terrain.h"
#include "unit.h"
#include "actions.h"
#include "algorithms.h"

using namespace std;

// Forward declaration of auxiliary functions
void printHLine(ostream& os, int n);
string getDpSymbol(dp_mode dp);
Grid<int> getFieldCosts(const Field& field, Unit* u);
bool performMove(ostream& os, istream& is, Field& field, Unit* u);

// load terrains and units into field
void loadMap(std::istream& is, Field& field) {
  //Fill in your code here
}


// Main loop for playing the game
void play(Field& field, istream& is, ostream& os)
{
    while (is)
    {
      displayField(os, field);

      // select unit

      // select action

      // perform action
      // A function called performAction is defined below.
      // You can use it or define your own version.

      // The following line is needed in task 1 and task2.
      // It avoids entering the next loop
      // when reaches the end of the input data.
      // Remove it in task 3 and task 4.
      if (is.eof()) break;
    }
}

// Display the field on the out stream os
void displayField(ostream& os, const Field& field, const Grid<bool>& grd, dp_mode dp)
{
    int height = field.getHeight();
    int width = field.getWidth();
    string dp_symbol = getDpSymbol(dp);

    os << endl;
    // Print the x coordinates
    os << "  ";
    for (int i = 0; i < width; i++)
        os << setw(3) << i << " ";
    os << endl;

    printHLine(os, width);
    for (int i = 0; i < height; i++) {
        os << setw(2) << i;
        for (int j = 0; j < width; j++) {
            os << '|';
            const Unit* u = field.getUnit(i,j);
            Terrain t = field.getTerrain(i, j);
            string sym;
            int width = 3;
            if (grd.inBounds(i,j) && grd[i][j]) {
                os << setw(1) << dp_symbol;
                width -= 1;
            }

            if (u != nullptr) sym += u->getSymbol();
            else sym += t.getSymbol();
            os << setw(width) << sym;
        }
        os << '|' << endl;
        printHLine(os, width);
    }
    os << endl;
}

// Print the horizontal line
void printHLine(ostream& os, int n)
{
    os << "  ";
    for (int i = 0; i < n; i++)
        os << "+---";
    os << "+" << endl;
}

// symbol used in displayField
string getDpSymbol(dp_mode dp) {
    return " ";
}

bool performAction(Field& field, istream& is, ostream& os, Unit* u, Action act) {
    switch(act) {
    case MOVE:
        return performMove(os, is, field, u);

    case SKIP:
        return true;

    default:
        os << "(Action not implemented yet)" << endl;
        return false;
    }
}

// Perform the move action
// The implementation is incomplete
bool performMove(ostream& os, istream& is, Field& field, Unit* u)
{
    // Display the reachable points
    Grid<bool> grd =
        searchReachable(getFieldCosts(field, u), u->getRow(), u->getCol(), u->getMovPoints());

    displayField(os, field, grd, DP_MOVE);

    return true;
}

// Convert field to costs
// The cost should depend on the terrain type and unit type
Grid<int> getFieldCosts(const Field& field, Unit* u)
{
    int h = field.getHeight();
    int w = field.getWidth();
    Grid<int> costs(h, w);

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) 
            costs[i][j] = 1;

    return costs;
}
