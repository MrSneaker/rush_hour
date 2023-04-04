#include "Puzzle.hpp"

using namespace std;

Puzzle::Puzzle()
{
}

Puzzle::~Puzzle()
{
}

void Puzzle::placeVehicule(vehicule v, plateau p)
{
    p.getVehicules().push_back(v);
}

void Puzzle::generateRandomPuzzle()
{
    plateau p;
    int nb_vehicules = rand() % 14 + 1;
    int length_startVec = rand() % 2 + 2;
    p.getVehicules().push_back(vehicule(length_startVec, p.getExitCol() - length_startVec, p.getExitRow(), true));
    for (int i = 0; i < nb_vehicules; ++i)
    {
        int position_col = rand() % 6;
        int position_row = rand() % 6;
        int length = rand() % 2 + 2;
        bool direction = rand() % 2;
        vehicule v(length, position_col, position_row, direction);
        while (!isValidPlacement(v, p))
        {
            int position_col = rand() % 6;
            int position_row = rand() % 6;
            int length = rand() % 2 + 2;
            bool direction = rand() % 2;
            vehicule v(length, position_col, position_row, direction);
        }
        placeVehicule(v, p);
    }
}