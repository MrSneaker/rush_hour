#include "State.hpp"
#include <assert.h>

State::State()
{
    isVisited = false;
    parent = nullptr;
}

State::State(const State &s)
{
    isVisited = s.isVisited;
    parent = s.parent;
    board = s.board;
}

State::~State()
{
}

bool State::operator==(const State &s) const
{
    return (s.board == this->board);
}

bool State::getIsVisited()
{
    return isVisited;
}

void State::setIsVisited(bool isVisited)
{
    this->isVisited = isVisited;
}

State *State::getParent() const
{
    return parent;
}

void State::setParent(State *parent)
{
    this->parent = parent;
}

const plateau &State::getBoard() const
{
    return board;
}

plateau &State::getBoard_aff()
{
    return board;
}

void State::setBoard(const plateau &board)
{
    this->board = board;
}