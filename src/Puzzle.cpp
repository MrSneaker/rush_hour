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
                cout << "blockedCount : " << blockedCount << endl;
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
    plateau p_test(p);
    p_test.getVehicules().push_back(v);
    p_test.updateBoard();
    s.setBoard(p_test);
    cout << endl;
    int res = g.breadthFirstSearch(s, 100000);
    if (res == -1 || res <= complexite)
        return false;
    complexite = res;
    return true;
}

void Puzzle::generateRandomPuzzle(std::promise<void> createPuzzlePromise)
{
    p.reset();

    int nb_vehicules = rand() % 6 + 10; // entre 10 et 15
    cout << "Nombre de véhicules : " << nb_vehicules << endl;
    int length_startVec = /*rand() % 2 +*/ 2;

    vehicule redCar(length_startVec, 0, p.getExitRow(), true);
    p.getVehicules().push_back(redCar);
    // length_startVec == 2 ? p.moveVehiculeB(p.getVehicules()[0], 4, 1) : p.moveVehiculeB(p.getVehicules()[0], 3, 1);

    p.updateBoard();
    for (int i = 0; i < nb_vehicules; ++i)
    {
        int iteration = 0;
        int position_col = rand() % 6;
        int position_row = rand() % 6;
        vehicule v = randomVehicule(position_row, position_col);
        while (!isValidPlacement(v) && iteration < 100)
        {
            cout << "itération dans randomGene : " << iteration << endl;
            v.getLength() == 2 ? v.setLength(3) : v.setLength(2);
            int position_col = rand() % 6;
            int position_row = rand() % 6;
            v = randomVehicule(position_row, position_col);
            iteration++;
        }
        if (iteration >= 100)
        {
            cout << "Impossible de placer le véhicule " << i << endl;
            break;
        }
        else
        {
            placeVehicule(v);
            p.updateBoard();
        }
    }
    createPuzzlePromise.set_value();
}

bool Puzzle::writePuzzle(string filename)
{
    ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        file << p.getExitRow() << " " << p.getExitCol() << endl;
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
    // cout << "Test de regression de la classe Puzzle" << endl;
    // cout << "------------------------------------" << endl;
    // cout << "Test de la fonction randomVehicule" << endl;
    // cout << "------------------------------------" << endl;

    // vehicule v = randomVehicule(0, 0);
    // cout << "Test de la fonction placeVehicule" << endl;
    // cout << "------------------------------------" << endl;

    // placeVehicule(v);
    // cout << "Test de la fonction isValidPlacement" << endl;
    // cout << "------------------------------------" << endl;
    // cout << "Test de la fonction generateRandomPuzzle" << endl;
    // cout << "------------------------------------" << endl;
    // generateRandomPuzzle();
    // cout << "Test de la fonction writePuzzle" << endl;
    // cout << "------------------------------------" << endl;
    // writePuzzle("./data/puzzle2test.txt");
}