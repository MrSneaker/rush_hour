#ifndef STATE_HPP
#define STATE_HPP

#include "plateau.hpp"
#include <vector>

class State
{
private:
    // tableau de plateau
    vector<plateau> tab_p;

public:
    State(plateau init);
    ~State();
    void possible_play();
};

#endif