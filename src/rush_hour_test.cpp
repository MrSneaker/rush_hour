#include "plateau.hpp"
#include "Graphe.hpp"

int main()
{

    plateau p, p2;
    // p.play();
    // p.displayBoard();
    // p2.displayBoard();
    // p2.play();
    State s, s2;
    // s.setBoard(p);
    // s.getBoard().win_board();
    // s2.setBoard(p2);
    // cout << "test" << endl;
    // cout << "s1 : " << endl;
    // // s.getBoard().displayBoard();
    // cout << "s2 : " << endl;
    // s2.getBoard().displayBoard();
    cout << (s == s2) << endl;
    // s.makeNeighbor();
    Graphe g;
    g.breadthFirstSearch(s);
    return 0;
}