#include "Graphe.hpp"

Graphe::Graphe(/* args */)
{
}

Graphe::~Graphe()
{
}

void Graphe::breadthFirstSearch(State s)
{
    // for (int i = 0; i < G.size(); i++)
    // {
    //     G[i].setIsVisited(false);
    // }
    q.push(s);

    s.setIsVisited(true);

    while (!q.empty())
    {
        State current = q.front();
        current.makeNeighbor();
        for (auto neighbour : current.getNeighbors())
        {
            if (!neighbour.getIsVisited())
            {
                neighbour.setIsVisited(true);
                // neighbour.getBoard().displayBoard();
                q.push(neighbour);
            }
        }
        q.pop();
    }
}