#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <memory>
#include "State.hpp"

using namespace std;

class Graphe
{
private:
    queue<State> q;
    struct hash_state
    {
        std::size_t operator()(const State &s) const
        {
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
    struct StateCompare
    {
        bool operator()(const State &s1, const State &s2) const
        {
            return (s1 == s2);
        }
    };
    unordered_map<State, State *, hash_state, StateCompare> map;

public:
    vector<State> path;
    Graphe(/* args */);
    ~Graphe();
    void makeNeighbor(State &s);
    void breadthFirstSearch(State G);
};

#endif