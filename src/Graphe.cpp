#include "Graphe.hpp"
#include <algorithm>

Graphe::Graphe(/* args */)
{
}

Graphe::~Graphe()
{
}

void Graphe::makeNeighbor(State &s, bool start_finder)
{
    int start = 0;
    bool backward = false;
    bool forward = true;
    plateau current_board = s.getBoard();
    int size = current_board.getVehicules().size();
    if (start_finder)
        start = 1;

    for (int i = start; i < size; i++)

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

int Graphe::breadthFirstSearch(State s)
{
    cout << "state avant process : " << endl;
    s.getBoard().displayBoard();
    cout << "processing.." << endl;
    int iteration = 0;
    q.push(s);
    std::pair<const State, State *> p_s(s, &s);
    map.insert(p_s);
    State win_state;
    s.setIsVisited(true);
    bool win = false;
    vector<State *> parents;
    while (!q.empty() && iteration < 50000)
    {
        State current = q.front();
        parents.push_back(new State(current));
        makeNeighbor(current, false);
        for (auto &neighbour : current.getNeighbors())
        {
            if (!neighbour.getIsVisited())
            {
                neighbour.setIsVisited(true);
                neighbour.setParent(parents.back());
                q.push(neighbour);
                std::pair<const State, State *> p_neighbour(neighbour, &neighbour);
                map.insert(p_neighbour);
                // cout << "neighbour : " << endl;
                // neighbour.getBoard().displayBoard();
                if (neighbour.getBoard().win_board())
                {
                    win_state = neighbour;
                    // cout << "test win_state : " << endl;
                    // win_state.getBoard().displayBoard();
                    win = true;
                    // break;
                }
            }
        }
        if (win)
            break;
        q.pop();
        ++iteration;
    }
    if (iteration >= 50000)
    {
        cout << "trop d'itération => puzzle irrésolvable" << endl;
        return -1;
    }
    path.push_back(win_state);
    State *parent = win_state.getParent();
    while (parent != nullptr)
    {
        path.push_back(*parent);
        parent = parent->getParent();
    }

    std::reverse(path.begin(), path.end());

    std::for_each(parents.begin(), parents.end(), std::default_delete<State>());
    while (!q.empty())
        q.pop();
    map.clear();

    return win_state.getBoard().getMoveCount();
}