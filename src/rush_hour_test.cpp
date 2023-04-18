#include "Graphe.hpp"
#include "Puzzle.hpp"
#include <time.h>

int main()
{
    srand(time(NULL));

    Puzzle p;
    p.test_regression();

    plateau pl;
    pl.test_regression();

    Graphe g;
    g.test_regression();

    return 0;
}