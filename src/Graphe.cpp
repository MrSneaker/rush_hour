#include "Graphe.hpp"

Graphe::Graphe(/* args */)
{
}

Graphe::~Graphe()
{
}

void Graphe::BreadthFirstSearch(std::vector<State> G, int start)
{
    for (int i = 0; i < G.size(); i++)
    {
        G[i].setIsVisited(false);
    }
    queue.push(G[start]);

    G[start].setIsVisited(true);

    while (!queue.empty())
    {
        State current = queue.front();
        for (auto neighbour : current.getNeighbors())
        {
            if (!neighbour.getIsVisited())
            {
                neighbour.setIsVisited(true);
                queue.push(neighbour);
            }
        }
        queue.pop();
    }
}