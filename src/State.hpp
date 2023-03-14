#ifndef STATE_HPP
#define STATE_HPP

#include "plateau.hpp"
#include <vector>

class State
{
private:
    plateau new_p;

public:
    vector<State> neighbour;
    bool isVisited;
    int ind;
    State(plateau init);
    ~State();
    void possible_play();
};

#endif