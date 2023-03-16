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
    q.push(s);
    State win_state;
    s.setIsVisited(true);
    // std::set<State, StateCompare> visited_states;
    // visited_states.insert(s);
    std::vector<State> visited_states;
    visited_states.push_back(s);
    while (!q.empty())
    {
        cout << "taille q : " << q.size() << endl;
        State current = q.front();
        current.getBoard().displayBoard();
        cout << "gagné ??" << endl;
        if (current.getBoard().win_board())
        {
            cout << "gagné !!" << endl;
            win_state = current;
            break;
        }
        cout << "alo" << endl;
        current.makeNeighbor();
        cout << "size : " << current.getNeighbors().size() << endl;
        for (auto neighbour : current.getNeighbors())
        {
            cout << "AAAA" << endl;
            // cout << (visited_states.find(neighbour) == visited_states.end()) << endl;
            bool ok = true;
            for (auto e : visited_states)
            {
                if (e == neighbour)
                {
                    ok = false;
                    break;
                }
            }
            if (!neighbour.getIsVisited() && ok)
            {
                cout << "alo2" << endl;
                neighbour.setIsVisited(true);
                q.push(neighbour);
                visited_states.push_back(neighbour);
            }
        }
        q.pop();
        cout << "taille q fin : " << q.size() << endl;
    }
    visited_states.clear();
    cout << "win state : " << endl;
    win_state.getBoard().displayBoard();
    cout << "move count : " << win_state.getBoard().getMoveCount() << endl;
}