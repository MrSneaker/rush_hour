#include "State.hpp"

State::State(plateau init)
{
    tab_p.push_back(init);
}

State::~State()
{
}

void State::possible_play()
{
    bool backward = false;
    bool forward = true;
    if (tab_p.empty())
        std::cout << "ya un souci mon reuf" << std::endl;
    else
    {
        for (int j = 0; tab_p[0].getVehicules().size(); j++)
        {
            vehicule v = tab_p[0].getVehicules()[j];
            int pas = 1;
            while (tab_p[0].moveVehicule(v, forward, pas) || tab_p[0].moveVehicule(v, backward, pas))
            {
                std::vector<vehicule> new_state(tab_p[0].getVehicules().size());
                new_state[j] = v;
                plateau new_p;
                new_p; // faire
                break; // on sort de la fonction une fois qu'on a
            }
        }
    }
}