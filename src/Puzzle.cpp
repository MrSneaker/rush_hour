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

vehicule Puzzle::randomVehicule(int row, int col)
{
    int length = rand() % 3 + 2;
    bool direction = rand() % 2; // 0 = vertical, 1 = horizontal
    vehicule v(length, row, col, direction);
    return v;
}

bool Puzzle::isValidPlacement(vehicule v, plateau p)
{
    if (v.getDirection())
    {
        if (v.getPositionCol() + v.getLength() > p.getSize())
        {
            return false;
        }
        for (int i = v.getPositionCol(); i < v.getPositionCol() + v.getLength(); i++)
        {
            if (p.getBoardState().board_state[v.getPositionRow()][i])
            {
                return false;
            }
        }
    }
    else
    {
        if (v.getPositionRow() + v.getLength() > p.getSize())
        {
            return false;
        }
        for (int i = v.getPositionRow(); i < v.getPositionRow() + v.getLength(); i++)
        {
            if (p.getBoardState().board_state[i][v.getPositionCol()])
            {
                return false;
            }
        }
    }
    return true;
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
        vehicule v = randomVehicule(position_row, position_col);
        while (!isValidPlacement(v, p))
        {
            int position_col = rand() % 6;
            int position_row = rand() % 6;
            v = randomVehicule(position_row, position_col);
        }
        placeVehicule(v, p);
    }
}
