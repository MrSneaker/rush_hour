#ifndef STATE_HPP
#define STATE_HPP

#include "plateau.hpp"
#include <vector>
#include <unordered_map>

class State
{
private:
    bool isVisited;          // true si l'état a déjà été visité
    vector<State> neighbors; // liste des états voisins
    State *parent;           // pointeur vers l'état parent
    int cost;                // nombre de coup pour arriver à cet état

    plateau board; // plateau de jeu

    struct StateCompare
    {
        bool operator()(const State &s1, const State &s2) const
        {
            return (s1 == s2);
        }
    };

    struct hash_plateau
    {
        std::size_t getHash(const plateau &p) const
        {
            std::vector<bool> states_vec;
            for (int i = 0; i < TAILLE; ++i)
            {
                for (int j = 0; j < TAILLE; ++j)
                {
                    bool tmp = p.getBoardState().board_state[i][j];
                    states_vec.push_back(tmp);
                }
            }
            std::size_t h1 = std::hash<std::vector<bool>>{}(states_vec);
            return h1;
        }
    };

    struct StateHash
    {
        std::size_t operator()(const State &s) const
        {
            hash_plateau hp;
            std::size_t h1 = hp.getHash(s.getBoard());
            return h1;
        }
    };

public:
    State();
    State(const State &s);
    ~State();

    bool operator==(const State &s) const;

    /* Getters et Setters */
    bool getIsVisited();
    void setIsVisited(bool isVisited);

    State *getParent() const;
    void setParent(State *parent);

    int getCost();
    void setCost(int cost);
    const plateau &getBoard() const;
    plateau &getBoard_aff();
    void setBoard(const plateau &board);

    vector<State> getNeighbors();

    /* Méthodes */
    void addNeighbor(State neighbor);
    void makeNeighbor();
};

#endif