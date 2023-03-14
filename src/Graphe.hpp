#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <queue>
#include <vector>
#include "State.hpp"

using namespace std;

class Graphe
{
private:
    queue<State> queue;

public:
    Graphe(/* args */);
    ~Graphe();
    void BreadthFirstSearch(std::vector<State> G, int start);
};

#endif