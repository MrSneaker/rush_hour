#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#define TAILLE 6

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "vehicule.h"

using namespace std;

class plateau
{

private:
    vector<vehicule> vehicules;
    char board[TAILLE][TAILLE];
    int exitRow;
    int exitCol;
    int vehiculRowStart, vehiculColStart, VehicleLength;
    int moveCount;
    bool vehiculDirection; // true = horizontal, false = vertical

public:
    plateau();
    ~plateau();

    void initBoard();
    void displayBoard();
    /*! \brief bouge le vehicule dans la direction indiquée en paramètre si c'est possible.*/
    /*! \param dir true pour avancer false pour reculer*/
    /*! \param pas entier désignant le nombre de case parcouru lors du déplacement*/
    void moveVehicule(vehicule &v, bool dir, int pas);
    void play();

    /* Getters et Setters */
    int getExitRow();
    void setExitRow(int exitRow);

    int getExitCol();
    void setExitCol(int exitCol);

    int getVehiculRowStart();
    void setVehiculRowStart(int vehiculRowStart);

    int getVehiculColStart();
    void setVehiculColStart(int vehiculColStart);

    int getVehicleLength();
    void setVehicleLength(int VehicleLength);

    int getMoveCount();
    void setMoveCount(int moveCount);

    bool getVehiculDirection();
    void setVehiculDirection(bool vehiculDirection);

    vector<vehicule> getVehicules();
    char getBoard(int row, int col);
};

#endif // __PLATEAU_H__