#include "plateau.hpp"
#include "Graphe.hpp"
#include "Affichage.hpp"
#include <time.h>

int main()
{
    srand(time(NULL));
    plateau p("data/puzzlesTXT/puzzle1.txt");
    State s;
    // // //     s2, s3;
    s.setBoard(p);

    // Puzzle pzle;
    // // pzle.generateRandomPuzzle();
    // // pzle.writePuzzle("data/puzzlesTXT/puzzle2.txt");
    // plateau p_test("data/puzzlesTXT/puzzle1.txt");
    // State s_test;
    // s_test.setBoard(p_test);
    // Graphe gtest;
    // clock_t start = clock();
    // int res = gtest.breadthFirstSearch(s_test, 10000);
    // cout << "nb coup : " << res << endl;
    // clock_t end = clock();
    // cout << "temps de process : " << (end - start) / (CLOCKS_PER_SEC / 1000) << " milisecondes." << endl;
    Affichage affichage;

    affichage.loadDisplay();

    return 0;
}