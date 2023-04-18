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
    void multi_task_validPlacement(int &res, Graphe g, State s, int depth);
    bool generatePuzzleWithBacktracking(int row, int col);
    void test_regression();
    int getComplexite();
};

#endif