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
        G[i].isVisited = false;
    }
    queue.push(G[start]);

    G[start].isVisited = true;

    while (!queue.empty())
    {
        State current = queue.front();
        for (auto neighbour : current.neighbour)
        {
            if (!neighbour.isVisited)
            {
                neighbour.isVisited = true;
                queue.push(neighbour);
            }
        }
        queue.pop();
    }
}