#include "Graphe.hpp"

Graphe::Graphe()
{
}

Graphe::~Graphe()
{
}

vector<State> Graphe::makeNeighbor(State s)
{
    vector<State> res;
    int start = 0;
    bool backward = false;
    bool forward = true;
    plateau current_board = s.getBoard();
    int size = current_board.getVehicules().size();
    for (int i = start; i < size; i++)
        for (int pas = 1; pas < 5; pas++)
        {
            vehicule vF = current_board.getVehicules()[i];
            vehicule vB = current_board.getVehicules()[i];
            // création si il existe, d'un voisin avec le véhicule i avançant de pas vers l'avant
            if (current_board.moveVehicule(vF, forward, pas, false))
            {
                plateau neighbor_board(current_board);
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], forward, pas, true);
                State neighbor_state;
                neighbor_state.setBoard(neighbor_board);
                // si l'état créé existe déjà dans la map, on ne l'ajoute pas
                bool exist = !(u_map.find(neighbor_state) == u_map.end());
                if (!exist)
                {
                    res.push_back(neighbor_state);
                }
            }
            // création si il existe, d'un voisin avec le véhicule i avançant de pas vers l'arrière
            if (current_board.moveVehicule(vB, backward, pas, false))
            {
                plateau neighbor_board(current_board);
                neighbor_board.moveVehicule(neighbor_board.getVehicules()[i], backward, pas, true);
                State neighbor_state;
                neighbor_state.setBoard(neighbor_board);
                bool exist = !(u_map.find(neighbor_state) == u_map.end());
                if (!exist)
                {
                    res.push_back(neighbor_state);
                }
            }
        }
    return res;
}

int Graphe::breadthFirstSearch(State s, int max_iterations)
{
    // initialisation de la situation de base
    int nb_coup = 0;
    int iteration = 0;
    q.push(s);
    // création de la pair pour l'ajout dans la map.
    std::pair<const State, State *> p_s(s, &s);
    u_map.insert(p_s);
    State win_state;
    s.setIsVisited(true);
    bool win = false;
    // vector de pointeur State pour stocker les parents des états
    // créés.
    vector<State *> parents;
    while (!q.empty() && iteration < max_iterations)
    {
        // current est l'état courant à traiter
        State current = q.front();
        // c'est le parent des états voisins à venir
        parents.push_back(new State(current));
        vector<State> neighbors = makeNeighbor(current);
        for (auto &neighbour : neighbors)
        {
            // on met à jour l'état voisin
            neighbour.setIsVisited(true);
            neighbour.setParent(parents.back());
            // on le met dans la queue pour le traiter
            q.push(neighbour);
            std::pair<const State, State *> p_neighbour(neighbour, &neighbour);
            // et dans la map pour éviter les doublons
            u_map.insert(p_neighbour);
            if (neighbour.getBoard().win_board())
            {
                win_state = neighbour;
                win = true;
            }
        }
        // l'état est traité, on le sort de la queue
        q.pop();
        ++iteration;
        if (win)
            break;
    }
    if (!win)
    {
        nb_coup = -1;
    }
    else // le nombre de coup = le nombre de mouvement du dernier plateau
        nb_coup = win_state.getBoard().getMoveCount();
    path.push_back(win_state);
    State *parent = win_state.getParent();
    // on remonte les parents pour avoir le chemin complet
    while (parent != nullptr)
    {
        path.push_back(*parent);
        parent = parent->getParent();
    }

    // on inverse l'ordre du vector path
    std::reverse(path.begin(), path.end());

    // on libère la mémoire sur le tas
    std::for_each(parents.begin(), parents.end(), std::default_delete<State>());

    // on nettoie les structures de la classe
    while (!q.empty())
        q.pop();
    u_map.clear();

    return nb_coup;
}

void Graphe::test_regression()
{
    cout << "Test de regression de la classe Graphe" << endl;

    Graphe g;
    plateau p("data/puzzlesTXT/puzzle1.txt");
    State s;
    s.setBoard(p);
    assert(g.breadthFirstSearch(s, 100000) == 14);

    cout << "------------------------------------" << endl;
}