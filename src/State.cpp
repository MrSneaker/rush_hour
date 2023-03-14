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

plateau State::getBoard()
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
    for (int i = 0; i < size; i++)

        for (int pas = 1; pas < 4; pas++)
        {

            // cout << "size vehicules boucle : " << board.getVehicules().size() << endl;
            vehicule vF = this->board.getVehicules()[i];
            vehicule vB = this->board.getVehicules()[i];
            // plateau *boardF = this->board;
            // plateau *boardB = this->board;
            // this->board.displayBoard();
            if (this->board.moveVehicule(vF, forward, pas, false))
            {
                // cout << "if 1" << endl;
                // this->board.displayBoard();
                std::vector<vehicule> new_states_vehicules;
                for (int i = 0; i < size; i++)
                {
                    new_states_vehicules.push_back(this->board.getVehicules()[i]);
                }
                plateau neighbor_board(new_states_vehicules, this->board.getExitRow(), this->board.getExitCol(), this->board.getVehiculRowStart(), this->board.getVehiculColStart(), this->board.getVehicleLength(), this->board.getVehiculDirection(), this->board.getMoveCount());
                // cout << "test avant: " << endl;
                // neighbor_board.displayBoard();
                // cout << "pos new v avant: " << neighbor_board.getVehicules()[i].getPositionRow() << " - " << neighbor_board.getVehicules()[i].getPositionCol() << endl;
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], forward, pas, true);
                // cout << "pos new v apres : " << neighbor_board.getVehicules()[i].getPositionRow() << " - " << neighbor_board.getVehicules()[i].getPositionCol() << endl;
                // cout << "test apres: " << endl;
                // neighbor_board.displayBoard();
                State neighbor_state;
                neighbor_state.board = neighbor_board;
                // cout << "i : " << i << endl;
                // neighbor_state.board.displayBoard();
                neighbors.push_back(neighbor_state);
            }
            if (this->board.moveVehicule(vB, backward, pas, false))
            {
                // cout << "if 2" << endl;
                // this->board.displayBoard();
                std::vector<vehicule> new_states_vehicules;
                for (int i = 0; i < size; i++)
                {
                    new_states_vehicules.push_back(this->board.getVehicules()[i]);
                }
                plateau neighbor_board(new_states_vehicules, this->board.getExitRow(), this->board.getExitCol(), this->board.getVehiculRowStart(), this->board.getVehiculColStart(), this->board.getVehicleLength(), this->board.getVehiculDirection(), this->board.getMoveCount());
                // cout << "pos new v avant: " << neighbor_board.getVehicules()[i].getPositionRow() << " - " << neighbor_board.getVehicules()[i].getPositionCol() << endl;
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], backward, pas, true);
                // cout << "pos new v apres : " << neighbor_board.getVehicules()[i].getPositionRow() << " - " << neighbor_board.getVehicules()[i].getPositionCol() << endl;
                State neighbor_state;
                // cout << "i : " << i << endl;
                neighbor_state.board = neighbor_board;
                // neighbor_state.board.displayBoard();
                neighbors.push_back(neighbor_state);
            }
        }
}