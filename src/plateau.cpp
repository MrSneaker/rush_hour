#include "plateau.hpp"
#include <assert.h>

plateau::plateau(string filename)
{
    moveCount = 0;
    exitRow = 2;
    exitCol = 5;
    vehiculRowStart = 0;
    vehiculColStart = 0;
    VehicleLength = 0;
    vehiculDirection = false;
    size = TAILLE;
    initBoard(filename);
}

void plateau::reset()
{
    vehicules.clear();
    moveCount = 0;
    exitRow = 2;
    exitCol = 5;
    vehiculRowStart = 0;
    vehiculColStart = 0;
    VehicleLength = 0;
    vehiculDirection = false;
}

plateau::plateau()
{
    moveCount = 0;
    exitRow = 2;
    exitCol = 5;
    vehiculRowStart = 0;
    vehiculColStart = 0;
    VehicleLength = 0;
    vehiculDirection = false;
    size = TAILLE;
}

plateau::plateau(const plateau &p)
{
    this->vehicules = p.vehicules;
    this->exitRow = p.exitRow;
    this->exitCol = p.exitCol;
    this->vehiculRowStart = p.vehiculRowStart;
    this->vehiculColStart = p.vehiculColStart;
    this->VehicleLength = p.VehicleLength;
    this->vehiculDirection = p.vehiculDirection;
    this->moveCount = p.moveCount;
    this->states = p.states;
    updateBoard();
}

plateau::~plateau()
{
}

void plateau::updateBoard()
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            board[i][j] = '.';
            states.board_state[i][j] = false;
        }
    }
    for (int i = 0; i < vehicules.size(); i++)
    {
        vehicule v = vehicules[i];
        char symbol = i == 0 ? 'X' : 'A' + i - 1;
        for (int j = 0; j < v.getLength(); j++)
        {
            if (v.getDirection())
            {
                board[v.getPositionRow()][v.getPositionCol() + j] = symbol;
                states.board_state[v.getPositionRow()][v.getPositionCol() + j] = true;
            }
            else
            {
                board[v.getPositionRow() + j][v.getPositionCol()] = symbol;
                states.board_state[v.getPositionRow() + j][v.getPositionCol()] = true;
            }
        }
    }
}

void plateau::initBoard(string filename)
{
    reset();
    ifstream infile(filename);
    infile >> exitRow >> exitCol;
    infile >> finalComplexity;
    int row, col, len, dir;
    while (infile >> row >> col >> len >> dir)
    {
        vehicule v(len, col, row, dir);
        // le premier vehicule doit etre rouge
        if (vehicules.size() == 0)
        {
            v.r = 255;
            v.g = 0;
            v.b = 0;
        }
        else
        {
            v.r = rand() % 150;
            v.g = rand() % 255;
            v.b = rand() % 255;
        }
        vehicules.push_back(v);
    }

    infile.close();
    // cout << "Nombre de vehicules : " << vehicules.size() << endl;
    // cout << "Complexite du plateau : " << finalComplexity << endl;
    assert(vehicules.size() > 0 && vehicules.size() <= 16 && "Le nombre de vehicules doit être compris entre 1 et 16");
    for (auto v : vehicules)
    {
        assert(v.getLength() >= 2 && v.getLength() <= 3 && "La longueur d'un vehicule doit être comprise entre 1 et 3");
        assert(v.getPositionCol() >= 0 && v.getPositionCol() < TAILLE && "La position d'un vehicule doit être comprise entre 0 et 5");
        assert(v.getPositionRow() >= 0 && v.getPositionRow() < TAILLE && "La position d'un vehicule doit être comprise entre 0 et 5");
    }
    updateBoard();
}

void plateau::displayBoard() const
{
    cout << endl;

    for (int i = 0; i < TAILLE; i++)
    {
        cout << i << "      ";
    }
    cout << endl
         << endl
         << endl;

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (board[i][j] == 'X')
                cout << "\033[1;31m";
            else
                for (int k = 0; k < vehicules.size(); k++)
                {
                    // si c'est la position de départ du vehicule
                    if (vehicules[k].getPositionRow() == i && vehicules[k].getPositionCol() == j)
                    {
                        cout << "\033[1;34m";
                        break;
                    }
                    else
                    {
                        cout << "\033[0m";
                    }
                }

            cout << board[i][j] << "      ";
        }
        cout << endl
             << endl
             << endl;
    }
    cout << "-------------------------------------------" << endl
         << endl;
}

bool plateau::moveVehiculeF(vehicule &v, int pas, bool effective)
{
    bool ok_to_go = false;
    if (v.getDirection())
    {
        bool out_of_bound = v.getPositionCol() + (v.getLength() - 1) + pas >= 6;
        if (!out_of_bound)
        {
            for (int i = 1; i <= pas; i++)
            {
                if (!states.board_state[v.getPositionRow()][v.getPositionCol() + (v.getLength() - 1) + i])
                    ok_to_go = true;
                else
                    ok_to_go = false;
                if (!ok_to_go)
                    break;
            }
        }
    }
    else
    {
        bool out_of_bound = v.getPositionRow() + (v.getLength() - 1) + pas >= 6;
        for (int i = 1; i <= pas; i++)
        {
            if (!out_of_bound)
                if (!states.board_state[v.getPositionRow() + (v.getLength() - 1) + i][v.getPositionCol()])
                    ok_to_go = true;
                else
                    ok_to_go = false;
            if (!ok_to_go)
                break;
        }
    }
    if (ok_to_go && effective)
    {
        v.moveForwardToDir(pas);
        states.board_state[v.getPositionRow()][v.getPositionCol()] = true;
        moveCount++;
    }
    return ok_to_go;
}

bool plateau::moveVehiculeB(vehicule &v, int pas, bool effective)
{
    // la même chose que dans moveVehiculeF mais on recule au lieu d'avancer.
    bool ok_to_go = false;
    if (v.getDirection())
    {
        bool out_of_bound = v.getPositionCol() - pas < 0;
        for (int i = 1; i <= pas; i++)
        {
            if (!out_of_bound)
                if (!states.board_state[v.getPositionRow()][v.getPositionCol() - i])
                    ok_to_go = true;
                else
                    ok_to_go = false;
            if (!ok_to_go)
                break;
        }
    }
    else
    {
        bool out_of_bound = v.getPositionRow() - pas < 0;
        for (int i = 1; i <= pas; i++)
        {
            if (!out_of_bound)
                if (!states.board_state[v.getPositionRow() - i][v.getPositionCol()])
                    ok_to_go = true;
                else
                    ok_to_go = false;
            if (!ok_to_go)
                break;
        }
    }
    if (ok_to_go && effective)
    {
        v.moveBackwardToDir(pas);
        states.board_state[v.getPositionRow()][v.getPositionCol()] = true;
        moveCount++;
    }
    return ok_to_go;
}

bool plateau::moveVehicule(vehicule &v, bool dir, int pas, bool effective)
{
    bool move_ok;
    if (dir)
    {
        move_ok = moveVehiculeF(v, pas, effective);
    }
    else
    {
        move_ok = moveVehiculeB(v, pas, effective);
    }
    updateBoard();
    // cout << "Move count: " << moveCount << endl;
    return move_ok;
}

bool plateau::win_board() const
{
    return (vehicules[0].getPositionCol() + (vehicules[0].getLength() - 1) == exitCol) && (vehicules[0].getPositionRow() == exitRow);
}

const int &plateau::getFinalComplexity()
{
    return finalComplexity;
}

const int &plateau::getSize() const
{
    return size;
}

int plateau::getExitRow()
{
    return exitRow;
}

void plateau::setExitRow(int exitRow)
{
    this->exitRow = exitRow;
}

int plateau::getExitCol()
{
    return exitCol;
}

void plateau::setExitCol(int exitCol)
{
    this->exitCol = exitCol;
}

int plateau::getVehiculRowStart()
{
    return vehiculRowStart;
}

void plateau::setVehiculRowStart(int vehiculRowStart)
{
    this->vehiculRowStart = vehiculRowStart;
}

int plateau::getVehiculColStart()
{
    return vehiculColStart;
}

void plateau::setVehiculColStart(int vehiculColStart)
{
    this->vehiculColStart = vehiculColStart;
}

int plateau::getVehicleLength()
{
    return VehicleLength;
}

void plateau::setVehicleLength(int VehicleLength)
{
    this->VehicleLength = VehicleLength;
}

bool plateau::getVehiculDirection()
{
    return vehiculDirection;
}

void plateau::setVehiculDirection(bool vehiculDirection)
{
    this->vehiculDirection = vehiculDirection;
}

vector<vehicule> &plateau::getVehicules()
{
    return vehicules;
}

void plateau::setVehicules(vector<vehicule> vehicules)
{
    this->vehicules = vehicules;
}

const board_state_struct &plateau::getBoardState() const
{
    return states;
}

const char &plateau::getBoard(int row, int col) const
{
    return board[row][col];
}

const int &plateau::getMoveCount() const
{
    return moveCount;
}

bool plateau::operator==(const plateau &p2) const
{
    // Comparaison des vecteurs de véhicules
    if (this->vehicules.size() != p2.vehicules.size())
    {
        return false;
    }
    for (unsigned long int i = 0; i < this->vehicules.size(); i++)
    {
        if (this->vehicules[i] != p2.vehicules[i])
        {
            return false;
        }
    }
    // Comparaison des tableaux de caractères
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (this->getBoard(i, j) != p2.getBoard(i, j))
            {
                return false;
            }
        }
    }
    // Comparaison des autres attributs
    if (this->getMoveCount() != p2.getMoveCount())
    {
        return false;
    }
    return true;
}

void plateau::test_regression()
{
    cout << "Test de régression de la classe plateau" << endl;

    plateau p("data/puzzlesTXT/puzzle1.txt");
    assert(p.getVehicules().size() == 13);

    plateau p2(p);
    assert(p2.getVehicules().size() == 13);
    assert(p == p2);

    assert(p.win_board() == false);

    assert(p.moveVehicule(p.getVehicules()[2], true, 1, true) == true);

    assert(p.getVehicules()[2].getPositionRow() == 1);

    p.updateBoard();
    assert((p == p2) == false);

    cout << "------------------------------------" << endl;
}
