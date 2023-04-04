#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "plateau.hpp"
#include "Graphe.hpp"
#include "vehicule.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Puzzle
{
private:
public:
    Puzzle();
    ~Puzzle();

    vehicule randomVehicule();
    void placeVehicule(vehicule v, plateau p, int row, int col);
    void isValidPlacement(vehicule v);
    void generateRandomPuzzle();
};

#endif