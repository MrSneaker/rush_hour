#include "State.hpp"

State::State(plateau init)
{
}

State::~State()
{
}

void State::possible_play()
{
    bool backward = false;
    bool forward = true;

    for (int j = 0; new_p.getVehicules().size(); j++)
    {
        vehicule v = new_p.getVehicules()[j];
        int pas = 1;
        while (new_p.moveVehicule(v, forward, pas) || new_p.moveVehicule(v, backward, pas))
        {
            std::vector<vehicule> new_state(new_p.getVehicules().size());
            new_state[j] = v;
            plateau new_p;
            new_p; // faire
            break; // on sort de la fonction une fois qu'on a
        }
    }
}