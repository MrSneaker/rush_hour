#include "Graphe.hpp"
#include <algorithm>

Graphe::Graphe(/* args */)
{
}

Graphe::~Graphe()
{
}

void Graphe::makeNeighbor(State &s)
{
    bool backward = false;
    bool forward = true;
    plateau current_board = s.getBoard();
    int size = current_board.getVehicules().size();
    for (int i = 0; i < size; i++)

        for (int pas = 1; pas < 4; pas++)
        {
            vehicule vF = current_board.getVehicules()[i];
            vehicule vB = current_board.getVehicules()[i];
            if (current_board.moveVehicule(vF, forward, pas, false))
            {
                plateau neighbor_board(current_board);
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], forward, pas, true);
                State neighbor_state;
                neighbor_state.setBoard(neighbor_board);
                bool exist = !(map.find(neighbor_state) == map.end());
                if (!exist)
                    s.addNeighbor(neighbor_state);
            }
            if (current_board.moveVehicule(vB, backward, pas, false))
            {
                plateau neighbor_board(current_board);
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], backward, pas, true);
                State neighbor_state;
                neighbor_state.setBoard(neighbor_board);
                bool exist = !(map.find(neighbor_state) == map.end());
                if (!exist)
                    s.addNeighbor(neighbor_state);
            }
        }
}

void Graphe::breadthFirstSearch(State s)
{
    cout << "processing.." << endl;
    q.push(s);
    std::pair<const State, State *> p_s(s, &s);
    map.insert(p_s);
    State win_state;
    s.setIsVisited(true);
    bool win = false;
    vector<State *> parents;
    while (!q.empty())
    {
        State current = q.front();
        parents.push_back(new State(current));
        makeNeighbor(current);
        for (auto &neighbour : current.getNeighbors())
        {
            if (!neighbour.getIsVisited())
            {
                neighbour.setIsVisited(true);
                neighbour.setParent(parents.back());
                q.push(neighbour);
                std::pair<const State, State *> p_neighbour(neighbour, &neighbour);
                map.insert(p_neighbour);
                if (neighbour.getBoard().win_board())
                {
                    win_state = neighbour;
                    win = true;
                    break;
                }
            }
        }
        if (win)
            break;
        q.pop();
    }
    cout << "--flag 5--" << endl;
    path.push_back(win_state);
    State *parent = win_state.getParent();
    while (parent != nullptr)
    {
        path.push_back(*parent);
        parent = parent->getParent();
    }

    std::reverse(path.begin(), path.end());

    std::for_each(parents.begin(), parents.end(), std::default_delete<State>());
}

void Graphe::BFS_from_win(vector<State> G, State s)
{
}