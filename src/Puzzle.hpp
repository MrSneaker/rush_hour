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
#include <random>

using namespace std;

class Puzzle
{
private:
public:
    Puzzle();
    ~Puzzle();

    vehicule randomVehicule(int row, int col);
    void placeVehicule(vehicule v, plateau p);
    bool isValidPlacement(vehicule v, plateau p);
    void generateRandomPuzzle();
};

#endif