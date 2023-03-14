#include "State.hpp"
#include <assert.h>

State::State()
{
    isVisited = false;
    parent = nullptr;
    cost = 0;
}

State::~State()
{
}

bool State::getIsVisited()
{
    return isVisited;
}

void State::setIsVisited(bool isVisited)
{
    this->isVisited = isVisited;
}

State *State::getParent()
{
    return parent;
}

void State::setParent(State *parent)
{
    this->parent = parent;
}

int State::getCost()
{
    return cost;
}

void State::setCost(int cost)
{
    this->cost = cost;
}

plateau *State::getBoard()
{
    return board;
}

void State::setBoard(plateau *board)
{
    this->board = board;
}

vector<State> State::getNeighbors()
{
    return neighbors;
}

void State::addNeighbor(State neighbor)
{
    neighbors.push_back(neighbor);
}
