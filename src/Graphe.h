#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>

using namespace std;

class Graphe
{
private:
    struct Cell
    {
        int node;
        vector<int *> front;
        vector<int *> back;
    };

public:
    Graphe(/* args */);
    ~Graphe();
};

#endif