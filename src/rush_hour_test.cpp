#include "plateau.hpp"
#include "Graphe.hpp"
#include "Affichage.hpp"
#include <time.h>

int main()
{
    srand(time(NULL));
    // plateau p, p2, p3;
    // p.play();
    // p3.play();
    // p.displayBoard();
    // p2.displayBoard();
    // p2.play();
    // State s;
    // // //     s2, s3;
    // s.setBoard(p);
    // s.getBoard().win_board();
    // s2.setBoard(p2);
    // s3.setBoard(p3);
    // cout << "test" << endl;
    // cout << "s1 : " << endl;
    // // s.getBoard().displayBoard();
    // cout << "s2 : " << endl;
    // s2.getBoard().displayBoard();
    // cout << (s == s2) << endl;
    // s.makeNeighbor();
    // s.setParent(&s2);
    // s2.setParent(&s3);
    // s.getBoard().displayBoard();
    // State *parent = s.getParent();
    // while (parent != nullptr)
    // {
    //     parent->getBoard().displayBoard();
    //     parent = parent->getParent();
    // }

    // Graphe g, gtest;
    // clock_t start = clock();
    // gtest.breadthFirstSearch(s);
    // clock_t end = clock();
    // cout << "temps de process : " << (end - start) / (CLOCKS_PER_SEC / 1000) << " milisecondes." << endl;
    Affichage affichage;

    affichage.loadDisplay();

    return 0;
}