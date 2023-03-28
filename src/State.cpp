#include "State.hpp"
#include <assert.h>

State::State()
{
    isVisited = false;
    parent = nullptr;
    cost = 0;
}

State::State(const State &s)
{
    isVisited = s.isVisited;
    neighbors = s.neighbors;
    parent = s.parent;
    cost = s.cost;
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

int State::getCost()
{
    return cost;
}

void State::setCost(int cost)
{
    this->cost = cost;
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

vector<State> State::getNeighbors()
{
    return neighbors;
}

void State::addNeighbor(State neighbor)
{
    neighbors.push_back(neighbor);
}

void State::makeNeighbor()
{
    bool backward = false;
    bool forward = true;
    int size = this->board.getVehicules().size();
    plateau current_board = this->board;
    for (int i = 0; i < size; i++)

        for (int pas = 1; pas < 4; pas++)
        {
            vehicule vF = current_board.getVehicules()[i];
            vehicule vB = current_board.getVehicules()[i];
            if (current_board.moveVehicule(vF, forward, pas, false))
            {
                bool exist = false;
                plateau neighbor_board(current_board);
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], forward, pas, true);
                State neighbor_state;
                neighbor_state.board = neighbor_board;
                if (!exist)
                    neighbors.push_back(neighbor_state);
            }
            if (current_board.moveVehicule(vB, backward, pas, false))
            {
                bool exist = false;
                plateau neighbor_board(current_board);
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], backward, pas, true);
                State neighbor_state;
                neighbor_state.board = neighbor_board;
                if (!exist)
                    neighbors.push_back(neighbor_state);
            }
        }
}