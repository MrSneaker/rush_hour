#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#define TAILLE 6

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "vehicule.h"

using namespace std;

class plateau {

    private:
        vector<vehicule> vehicules;
        char board[TAILLE][TAILLE];
        int exitRow;
        int exitCol;
        int vehiculRowStart, vehiculColStart, VehicleLength;
        bool vehiculDirection;

    public:

    plateau();
    ~plateau();

    void initBoard();
    void displayBoard();

};


#endif // __PLATEAU_H__