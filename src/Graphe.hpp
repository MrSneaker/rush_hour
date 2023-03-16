#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <queue>
#include <set>
#include <vector>
#include "State.hpp"

using namespace std;

class Graphe
{
private:
    queue<State> q;

public:
    Graphe(/* args */);
    ~Graphe();
    void breadthFirstSearch(State G);
};

#endif