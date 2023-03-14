#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#define TAILLE 6

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "vehicule.hpp"

using namespace std;

struct board_state_struct
{
    bool board_state[TAILLE][TAILLE];
};

class plateau
{

private:
    vector<vehicule> vehicules;
    char board[TAILLE][TAILLE];
    board_state_struct states;
    int exitRow;
    int exitCol;
    int vehiculRowStart, vehiculColStart, VehicleLength;
    int moveCount;
    bool vehiculDirection; // true = horizontal, false = vertical

public:
    plateau();
    plateau(vector<vehicule> vehicules, int exitRow, int exitCol, int vehiculRowStart, int vehiculColStart, int VehicleLength, bool vehiculDirection, int moveCount);
    ~plateau();

    void initBoard();
    void displayBoard();
    /*! \brief bouge le vehicule dans la direction indiquée en paramètre si c'est possible.*/
    /*! \param dir true pour avancer false pour reculer*/
    /*! \param pas entier désignant le nombre de case parcouru lors du déplacement*/
    /*! \param effective bool permettant de réaliser un mouvement effectif ou juste un test*/
    bool moveVehicule(vehicule &v, bool dir, int pas, bool effective);
    bool moveVehiculeF(vehicule &v, int pas, bool effective);
    bool moveVehiculeB(vehicule &v, int pas, bool effective);
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

    vector<vehicule> &getVehicules();
    void setVehicules(vector<vehicule> vehicules);
    board_state_struct getBoardState();
    char getBoard(int row, int col);
};

#endif // __PLATEAU_H__