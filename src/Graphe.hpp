#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <memory>
#include <assert.h>
#include "State.hpp"

using namespace std;

class Graphe
{
private:
    // queue stockant les situations de jeu à traiter dans le graphe.
    queue<State> q;

    // structure de hashage pour la map
    struct hash_state
    {
        std::size_t operator()(const State &s) const
        {
            // chaque booléen de board_state est stocké dans ce vector
            std::vector<bool> states_vec;
            for (int i = 0; i < TAILLE; ++i)
            {
                for (int j = 0; j < TAILLE; ++j)
                {
                    bool tmp = s.getBoard().getBoardState().board_state[i][j];
                    states_vec.push_back(tmp);
                }
            }
            std::size_t h1 = std::hash<std::vector<bool>>{}(states_vec);
            return h1;
        }
    };

    // structure de comparaison pour la map
    struct StateCompare
    {
        bool operator()(const State &s1, const State &s2) const
        {
            return (s1 == s2);
        }
    };

    // unordored_map stockant les états déjà visités.
    unordered_map<State, State *, hash_state, StateCompare> u_map;

public:
    // vector stockant le chemin de résolution du graphe.
    vector<State> path;

    Graphe();
    ~Graphe();

    // fonction de création des états voisins renvoyant les voisins de l'état en paramètre.
    vector<State> makeNeighbor(State s);

    // fonction de parcours de graphe en largeur, renvoyant un entier correspondant au nombre de coup
    // pour résolution, et -1 si irrésolvable.
    int breadthFirstSearch(State G, int max_iterations);

    void test_regression();
};

#endif