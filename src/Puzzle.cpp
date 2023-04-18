#include "Puzzle.hpp"
#include "Graphe.hpp"
#include <future>

using namespace std;

Puzzle::Puzzle()
{
    complexite = 0;
}

Puzzle::~Puzzle()
{
}

void Puzzle::placeVehicule(vehicule v)
{
    p.getVehicules().push_back(v);
}

vehicule Puzzle::randomVehicule(int row, int col)
{
    int length = rand() % 2 + 2;
    bool direction = rand() % 2; // 0 = vertical, 1 = horizontal

    vehicule v(length, row, col, direction);
    return v;
}

bool Puzzle::isValidPlacement(vehicule &v)
{
    Graphe g;
    State s;
    int blockedCount = 0;

    if (v.getDirection())
    {
        if (v.getPositionCol() + v.getLength() > p.getSize())
        {
            return false;
        }
        for (int i = v.getPositionCol(); i < v.getPositionCol() + v.getLength(); i++)
        {
            if (p.getBoardState().board_state[v.getPositionRow()][i])
            {
                return false;
            }
        }

        // Vérification des nouvelles règles pour les véhicules horizontaux
        for (int col = 0; col < p.getSize(); col++)
        {
            // verifie que le nombre de véhicule bloqué est inférieur à 3 ou 2 ( qu'il n'ai pas trois vehicule bloqué)
            // exemple : 3 vehicule de taille 2 qui sont sur la même ligne et dans la même direction
            if (p.getBoardState().board_state[v.getPositionRow()][col])
            {
                blockedCount++;
            }
            else
            {
                blockedCount = 0;
            }

            if (blockedCount == 3 || (blockedCount == 2 && v.getLength() == 3))
            {
                return false;
            }
        }
        // je ne veux pas de véhicule qui soit sur la ligne de sortie à l'horizontal
        if (v.getPositionRow() == p.getExitRow())
        {
            return false;
        }
    }
    else
    {
        if (v.getPositionRow() + v.getLength() > p.getSize())
        {
            return false;
        }
        for (int i = v.getPositionRow(); i < v.getPositionRow() + v.getLength(); i++)
        {
            if (p.getBoardState().board_state[i][v.getPositionCol()])
            {
                return false;
            }
        }

        // Vérification des nouvelles règles pour les véhicules verticaux
        for (int row = 0; row < p.getSize(); row++)
        {
            if (p.getBoardState().board_state[row][v.getPositionCol()])
            {
                blockedCount++;
            }
            else
            {
                blockedCount = 0;
            }

            if (blockedCount == 3 || (blockedCount == 2 && v.getLength() == 3))
            {
                return false;
            }
        }
    }
    // on test si v est plaçable sur un plateau tampon, avec un parcour de graphe de celui-ci.
    plateau p_test(p);
    p_test.getVehicules().push_back(v);
    p_test.updateBoard();
    s.setBoard(p_test);

    int res = g.breadthFirstSearch(s, 100000);

    // si la situation est irrésolvable ou pas mieux que la précédente,
    // on ne la garde pas.
    if (res == -1 || res <= complexite)
        return false;
    complexite = res;
    return true;
}

bool Puzzle::generateRandomPuzzle(std::promise<void> createPuzzlePromise)
{
    // reset du plateau
    p.reset();
    // on retire une nouvelle graine aléatoire
    srand(time(NULL));
    p.setExitRow(rand() % 5 + 1);
    int nb_vehicules = rand() % 6 + 10; // entre 10 et 15
    int length_startVec = 2;

    // on place la voiture à sortir
    vehicule redCar(length_startVec, 0, p.getExitRow(), true);
    p.getVehicules().push_back(redCar);

    p.updateBoard();
    for (int i = 0; i < nb_vehicules; ++i)
    {
        // on compte le nombre de tours pour limiter le temps d'execution.
        int iteration = 0;
        // on place un véhicule aléatoire
        int position_col = rand() % 6;
        int position_row = rand() % 6;

        vehicule v = randomVehicule(position_row, position_col);

        while (!isValidPlacement(v) && (iteration < 100)) // on vérifie que le véhicule est bien placable
        {
            // on va retirer un nouveau véhicule aléatoire tant que le précédent n'est pas placable

            // on change la taille du véhicule
            v.getLength() == 2 ? v.setLength(3) : v.setLength(2);
            // on change la position du véhicule
            int position_col = rand() % 6;
            int position_row = rand() % 6;
            v = randomVehicule(position_row, position_col);
            iteration++;
        }
        if (iteration >= 100)
        {
            break;
        }
        else // on place le véhicule et on met à jour le plateau
        {
            placeVehicule(v);
            p.updateBoard();
        }
    }
    createPuzzlePromise.set_value();

    return true;
}

bool Puzzle::writePuzzle(string filename)
{
    ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        file << p.getExitRow() << " " << p.getExitCol() << endl;
        file << complexite << endl;
        for (int i = 0; i < p.getVehicules().size(); i++)
        {
            vehicule v = p.getVehicules()[i];
            file << v.getPositionRow() << " " << v.getPositionCol() << " " << v.getLength() << " " << v.getDirection() << endl;
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

int Puzzle::getComplexite()
{
    return complexite;
}

void Puzzle::test_regression()
{
    Puzzle p;
    cout << "Test de regression de la classe Puzzle" << endl;
    cout << "------------------------------------" << endl;
    cout << "Test de la fonction randomVehicule" << endl;
    cout << "------------------------------------" << endl;

    vehicule v = p.randomVehicule(2, 5);
    vehicule v2 = p.randomVehicule(2, 5);
    assert(v == v2);

    cout << "Test de la fonction placeVehicule" << endl;
    cout << "------------------------------------" << endl;

    p.placeVehicule(v);
    assert(p.p.getVehicules().size() == 1);

    cout << "Test de la fonction isValidPlacement" << endl;
    cout << "------------------------------------" << endl;

    assert(p.isValidPlacement(v2) == false);

    // cout << "Test de la fonction generateRandomPuzzle" << endl;
    // cout << "------------------------------------" << endl;
    // Puzzle p1;
    // std::promise<void> createPuzzlePromise;
    // assert(p1.generateRandomPuzzle(std::move(createPuzzlePromise)) == true);
}