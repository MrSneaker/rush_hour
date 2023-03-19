#include "State.hpp"
#include <assert.h>

State::State()
{
    isVisited = false;
    parent = nullptr;
    cost = 0;
}

State::State(bool isVisited, vector<State> neighbors, State *parent, int cost, plateau board)
{
    isVisited = this->isVisited;
    neighbors = this->neighbors;
    parent = this->parent;
    cost = this->cost;
    board = this->board;
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

void State::makeNeighbor(const vector<State> &already_known)
{
    bool backward = false;
    bool forward = true;
    int size = this->board.getVehicules().size();
    plateau current_board = this->board;
    for (int i = 0; i < size; i++)

        for (int pas = 1; pas < 4; pas++)
        {

            // cout << "size vehicules boucle : " << board.getVehicules().size() << endl;
            vehicule vF = current_board.getVehicules()[i];
            vehicule vB = current_board.getVehicules()[i];
            // plateau *boardF = this->board;
            // plateau *boardB = this->board;
            // this->board.displayBoard();
            if (current_board.moveVehicule(vF, forward, pas, false))
            {
                bool exist = false;
                // cout << "if 1" << endl;
                // this->board.displayBoard();
                std::vector<vehicule> new_states_vehicules;
                for (const auto &v : current_board.getVehicules())
                {
                    new_states_vehicules.push_back(v);
                }
                plateau neighbor_board(new_states_vehicules, current_board.getExitRow(), current_board.getExitCol(), current_board.getVehiculRowStart(), current_board.getVehiculColStart(), current_board.getVehicleLength(), current_board.getVehiculDirection(), current_board.getMoveCount(), current_board.getBoardState());
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
                for (const auto &n : already_known)
                {
                    if (n == neighbor_state)
                    {
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                    neighbors.push_back(neighbor_state);
                // cout << "neighbor isVisited : " << neighbors.back().isVisited << endl;
            }
            if (current_board.moveVehicule(vB, backward, pas, false))
            {
                bool exist = false;
                // cout << "if 2" << endl;
                // current_board.displayBoard();
                std::vector<vehicule> new_states_vehicules;
                for (const auto &v : current_board.getVehicules())
                {
                    new_states_vehicules.push_back(v);
                }
                plateau neighbor_board(new_states_vehicules, current_board.getExitRow(), current_board.getExitCol(), current_board.getVehiculRowStart(), current_board.getVehiculColStart(), current_board.getVehicleLength(), current_board.getVehiculDirection(), current_board.getMoveCount(), current_board.getBoardState());
                // cout << "pos new v avant: " << neighbor_board.getVehicules()[i].getPositionRow() << " - " << neighbor_board.getVehicules()[i].getPositionCol() << endl;
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], backward, pas, true);
                // cout << "pos new v apres : " << neighbor_board.getVehicules()[i].getPositionRow() << " - " << neighbor_board.getVehicules()[i].getPositionCol() << endl;
                State neighbor_state;
                // cout << "i : " << i << endl;
                neighbor_state.board = neighbor_board;
                // neighbor_state.board.displayBoard();
                for (const auto &n : already_known)
                {
                    if (n == neighbor_state)
                    {
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                    neighbors.push_back(neighbor_state);
            }
        }
}