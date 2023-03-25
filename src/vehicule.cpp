#include "vehicule.hpp"

vehicule::vehicule(int longueur, int positionCol, int positionRow, bool orientation)
{
    this->length = longueur;
    this->positionCol = positionCol;
    this->positionRow = positionRow;
    this->direction = orientation;
    r, g, b = 0;
}

vehicule::~vehicule()
{
}

const int &vehicule::getLength() const
{
    return this->length;
}

void vehicule::setLength(int longueur)
{
    this->length = longueur;
}

const int &vehicule::getPositionCol() const
{
    return this->positionCol;
}

void vehicule::setPositionCol(int positionCol)
{
    this->positionCol = positionCol;
}

const int &vehicule::getPositionRow() const
{
    return this->positionRow;
}

void vehicule::setPositionRow(int positionRow)
{
    this->positionRow = positionRow;
}

const bool &vehicule::getDirection() const
{
    return this->direction;
}

void vehicule::setDirection(bool orientation)
{
    this->direction = orientation;
}

void vehicule::moveForwardToDir(int pas)
{
    if (direction == true) // si horizontal
    {
        setPositionCol(this->positionCol + pas);
    }
    else // si vertical
    {
        setPositionRow(this->positionRow + pas);
    }
}

void vehicule::moveBackwardToDir(int pas)
{
    if (direction == true) // si horizontal
    {
        setPositionCol(this->positionCol - pas);
    }
    else // si vertical
    {
        setPositionRow(this->positionRow - pas);
    }
}

bool vehicule::operator!=(const vehicule &v) const
{
    return this->length != v.length && this->positionCol != v.positionCol && this->positionRow != v.positionRow && this->direction != v.direction;
}

bool vehicule::operator==(const vehicule &v) const
{
    return this->length == v.length && this->positionCol == v.positionCol && this->positionRow == v.positionRow && this->direction == v.direction;
}
