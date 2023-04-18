#ifndef STATE_HPP
#define STATE_HPP

#include "plateau.hpp"
#include <vector>
#include <unordered_map>

class State
{
private:
    // true si l'état a déjà été visité
    bool isVisited;

    // pointeur vers l'état parent
    State *parent;

    // plateau de jeu
    plateau board;

public:
    State();
    // constructeur par copie
    State(const State &s);
    ~State();

    // operateur d'égalité
    bool operator==(const State &s) const;

    /* Getters et Setters */
    bool getIsVisited();
    void setIsVisited(bool isVisited);

    State *getParent() const;
    void setParent(State *parent);

    const plateau &getBoard() const;

    // accesseur non const du plateau pour affichage
    plateau &getBoard_aff();

    void setBoard(const plateau &board);

    vector<State> &getNeighbors();
};

#endif