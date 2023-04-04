#include "Puzzle.hpp"

using namespace std;

Puzzle::Puzzle()
{
}

Puzzle::~Puzzle()
{
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