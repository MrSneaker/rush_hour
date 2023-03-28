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

    vector<State> &getNeighbors();

    /* Méthodes */
    void addNeighbor(State neighbor);
};

#endif