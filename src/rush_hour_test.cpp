#include "plateau.hpp"
#include "Graphe.hpp"

int main()
{

    plateau p;
    p.displayBoard();
    // p.play();
    p.displayBoard();
    State s;
    s.setBoard(p);
    s.makeNeighbor();
    Graphe g;
    g.breadthFirstSearch(s);
    return 0;
}