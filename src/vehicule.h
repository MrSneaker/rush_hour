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
    vehicule(int length, int positionCol, int positionRow, bool direction);
    ~vehicule();

    // --- Getters & Setters ---

    int getLength();
    void setLength(int length);

    int getPositionCol();
    void setPositionCol(int positionCol);

    int getPositionRow();
    void setPositionRow(int positionRow);

    bool getDirection();
    void setDirection(bool direction);

    void moveForwardToDir(int pas);
    void moveBackwardToDir(int pas);

    // surcharge de l'opérateur ==
    bool operator!=(const vehicule &v) const;
};

#endif // _VEHICULE_H__