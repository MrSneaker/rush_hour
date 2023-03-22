#include "Graphe.hpp"

Graphe::Graphe(/* args */)
{
}

Graphe::~Graphe()
{
}

struct StateCompare
{
    bool operator()(const State &s1, const State &s2) const
    {
        return (s1 == s2);
    }
};

void Graphe::breadthFirstSearch(State s)
{
    cout << "processing.." << endl;
    q.push(s);
    State win_state;
    s.setIsVisited(true);
    bool win = false;
    vector<State *> parents;
    vector<State> visited_states;
    visited_states.push_back(s);
    while (!q.empty())
    {
        State current = q.front();
        parents.push_back(new State(current));
        current.makeNeighbor(visited_states);
        for (auto &neighbour : current.getNeighbors())
        {
            bool ok = true;
            if (!neighbour.getIsVisited() && ok)
            {
                neighbour.setIsVisited(true);
                neighbour.setParent(parents.back());
                q.push(neighbour);
                visited_states.push_back(neighbour);
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
    cout << "win state : " << endl;
    win_state.getBoard().displayBoard();
    cout << "move count : " << win_state.getBoard().getMoveCount() << endl;
    std::cout << "parent :" << std::endl;
    State *parent = win_state.getParent();
    while (parent != nullptr)
    {
        parent->getBoard().displayBoard();
        cout << parent->getBoard().getMoveCount() << endl;
        parent = parent->getParent();
    }
    for (const auto &e : parents)
        delete e;
}