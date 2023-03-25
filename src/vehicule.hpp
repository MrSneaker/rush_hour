#ifndef __VEHICULE_H__
#define __VEHICULE_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class vehicule
{
private:
    int length;
    int positionCol;
    int positionRow;
    bool direction; // true = horizontal, false = vertical

public:
    int r, g, b;

    vehicule(int length, int positionCol, int positionRow, bool direction);
    ~vehicule();

    // --- Getters & Setters ---

    const int &getLength() const;
    void setLength(int length);

    const int &getPositionCol() const;
    void setPositionCol(int positionCol);

    const int &getPositionRow() const;
    void setPositionRow(int positionRow);

    const bool &getDirection() const;
    void setDirection(bool direction);

    void moveForwardToDir(int pas);
    void moveBackwardToDir(int pas);

    // surcharge de l'opérateur ==
    bool operator!=(const vehicule &v) const;
    bool operator==(const vehicule &v) const;
};

#endif // _VEHICULE_H__