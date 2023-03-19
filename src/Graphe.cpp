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
    // std::set<State, StateCompare> visited_states;
    // visited_states.insert(s);
    std::vector<State> visited_states;
    visited_states.push_back(s);
    while (!q.empty())
    {
        // cout << "taille q : " << q.size() << endl;
        State current = q.front();
        // current.getBoard().displayBoard();
        // cout << "gagné ??" << endl;

        // cout << "alo" << endl;
        current.makeNeighbor(visited_states);
        // cout << "size : " << current.getNeighbors().size() << endl;
        for (auto &neighbour : current.getNeighbors())
        {
            // cout << "AAAA" << endl;
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
                // cout << "alo2" << endl;
                neighbour.setIsVisited(true);
                neighbour.setParent(&current);
                if (neighbour.getBoard().win_board())
                {
                    // cout << "gagné !!" << endl;
                    win_state = neighbour;
                    win = true;
                    break;
                }
                q.push(neighbour);
                visited_states.push_back(neighbour);
                if (*neighbour.getParent() == current)
                {
                    // cout << ";;;;;;;;)))))))))" << endl;
                    // cout << "1 : " << endl;
                    // neighbour.getParent()->getBoard().displayBoard();
                    // cout << "2 : " << endl;
                    // current.getBoard().displayBoard();
                    // cout << "3 : " << endl;
                    // neighbour.getBoard().displayBoard();
                }
                else
                {
                    // cout << ";(((((((" << endl;
                }
            }
        }
        if (win)
            break;
        q.pop();
        // cout << "taille q fin : " << q.size() << endl;
    }
    visited_states.clear();
    cout << "win state : " << endl;
    win_state.getBoard().displayBoard();
    cout << "move count : " << win_state.getBoard().getMoveCount() << endl;
    std::cout << "parent :" << std::endl;
    State *parent = win_state.getParent();
    if (parent != nullptr)
    {
        parent->getBoard().displayBoard();
        cout << parent->getBoard().getMoveCount() << endl;
        parent = parent->getParent();
        parent->getBoard().displayBoard();
        cout << parent->getBoard().getMoveCount() << endl;
        parent = parent->getParent();
    }
}