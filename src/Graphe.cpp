#include "Graphe.hpp"
#include <algorithm>

Graphe::Graphe(/* args */)
{
}

Graphe::~Graphe()
{
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
        current.makeNeighbor();
        for (auto &neighbour : current.getNeighbors())
        {
            bool ok = (map.find(neighbour) == map.end());
            if (!neighbour.getIsVisited() && ok)
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
    path.push_back(win_state);
    State *parent = win_state.getParent();
    while (parent != nullptr)
    {
        // parent->getBoard().displayBoard();
        // ajoute le parent dans le vecteur path
        path.push_back(*parent);
        // cout << parent->getBoard().getMoveCount() << endl;
        parent = parent->getParent();
    }

    // on inverse g pour avoir le chemin dans le bon sens
    std::reverse(path.begin(), path.end());

    for (const auto &e : parents)
        delete e;
}