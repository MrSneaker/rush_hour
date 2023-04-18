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
#include <future>
#include <assert.h>

using namespace std;

class Puzzle
{
private:
    int complexite;

public:
    Puzzle();
    plateau p;
    ~Puzzle();

    vehicule randomVehicule(int row, int col);
    void placeVehicule(vehicule v);
    bool isValidPlacement(vehicule &v);
    bool generateRandomPuzzle(std::promise<void> createPuzzlePromise);
    bool writePuzzle(string filename);
    void test_regression();
    int getComplexite();
};

#endif