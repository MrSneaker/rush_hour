#ifndef STATES_HPP
#define STATES_HPP

#include "plateau.hpp"
#include <vector>

class States
{
private:
    // tableau de plateau
    vector<plateau> tab_p;

public:
    States(plateau init);
    ~States();
};

#endif