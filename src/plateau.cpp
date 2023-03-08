#include "plateau.h"
#include <assert.h>

plateau::plateau()
{
    initBoard();
    moveCount = 0;
    exitRow = 0;
    exitCol = 0;
    vehiculRowStart = 0;
    vehiculColStart = 0;
    VehicleLength = 0;
    vehiculDirection = false;
}

plateau::~plateau()
{
}

void plateau::initBoard()
{
    ifstream infile("data/puzzle.txt");
    infile >> exitRow >> exitCol;
    infile >> vehiculRowStart >> vehiculColStart >> VehicleLength >> vehiculDirection;
    int row, col, len, dir;
    while (infile >> row >> col >> len >> dir)
    {
        vehicules.push_back(vehicule(len, col, row, dir));
    }
    infile.close();

    assert(vehicules.size() > 0 && vehicules.size() <= 16 && "Le nombre de vehicules doit être compris entre 1 et 16");
    for (auto v : vehicules)
    {
        assert(v.getLength() >= 2 && v.getLength() <= 3 && "La longueur d'un vehicule doit être comprise entre 1 et 4");
        assert(v.getPositionCol() >= 0 && v.getPositionCol() < TAILLE && "La position d'un vehicule doit être comprise entre 0 et 5");
        assert(v.getPositionRow() >= 0 && v.getPositionRow() < TAILLE && "La position d'un vehicule doit être comprise entre 0 et 5");
    }
}

void plateau::displayBoard()
{
    cout << endl;

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            board[i][j] = '.';
        }
    }

    board[exitRow][exitCol] = 'E';
    for (int i = 0; i < vehicules.size(); i++)
    {
        vehicule v = vehicules[i];
        char symbol = i == 0 ? 'X' : 'A' + i - 1;
        for (int j = 0; j < v.getLength(); j++)
        {
            if (v.getDirection())
            {

                board[v.getPositionRow()][v.getPositionCol() + j] = symbol;
            }
            else
            {
                board[v.getPositionRow() + j][v.getPositionCol()] = symbol;
            }
        }
    }
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
            else if (board[i][j] == 'E')
                cout << "\033[1;32m";
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

void plateau::moveVehicule(vehicule &v, bool dir, int pas)
{
    bool ok_to_go = false;
    if (dir)
    {
        for (int j = 0; j < vehicules.size(); j++)
        {
            if (v != vehicules[j])
            {
                if (v.getDirection())
                {
                    ok_to_go = v.getPositionCol() + v.getLength() + pas != vehicules[j].getPositionCol() && v.getPositionRow() != vehicules[j].getPositionRow() && v.getPositionCol() + v.getLength() + pas <= TAILLE;
                }
                else
                {
                    ok_to_go = v.getPositionRow() + v.getLength() + pas != vehicules[j].getPositionRow() && v.getPositionCol() != vehicules[j].getPositionCol() && v.getPositionRow() + v.getLength() + pas <= TAILLE;
                }
                if (!ok_to_go)
                    break;
            }
        }
        cout << "ok_to_go: " << ok_to_go << endl;
        cout << "pas: " << pas << endl;
        if (ok_to_go)
        {
            v.moveForwardToDir(pas);
            moveCount++;
        }
        else
        {
            cout << "Impossible de bouger le vehicule" << endl;
        }
        if (ok_to_go)
            moveCount++;
    }
    else
    {
        for (int j = 0; j < vehicules.size(); j++)
        {
            if (v != vehicules[j])
            {
                if (v.getDirection())
                {
                    ok_to_go = v.getPositionCol() - pas != vehicules[j].getPositionCol() + vehicules[j].getLength() && v.getPositionRow() != vehicules[j].getPositionRow() && v.getPositionCol() - pas > 0 && v.getPositionRow() > 0;
                }
                else
                {
                    ok_to_go = v.getPositionRow() - pas != vehicules[j].getPositionRow() + vehicules[j].getLength() && v.getPositionCol() != vehicules[j].getPositionCol() && v.getPositionRow() - pas > 0 && v.getPositionCol() > 0;
                }
                if (!ok_to_go)
                    break;
            }
        }
        if (ok_to_go)
        {
            v.moveBackwardToDir(pas);
            moveCount++;
        }
        else
        {
            cout << "Impossible de bouger le vehicule" << endl;
        }
        if (ok_to_go)
            moveCount++;
    }
    cout << "Move count: " << moveCount << endl;
}

void plateau::play()
{
    moveVehicule(vehicules[1], false, 1);
    displayBoard();
    moveVehicule(vehicules[1], true, 2);
    displayBoard();
    moveVehicule(vehicules[1], true, 1);
    displayBoard();
    moveVehicule(vehicules[1], true, 1);
    displayBoard();
    moveVehicule(vehicules[1], false, 1);
    displayBoard();
}
//------------------------------------------------------------------------------

int plateau::getExitRow()
{
    return exitRow;
}

void plateau::setExitRow(int exitRow)
{
    exitRow = exitRow;
}

int plateau::getExitCol()
{
    return exitCol;
}

void plateau::setExitCol(int exitCol)
{
    exitCol = exitCol;
}

int plateau::getVehiculRowStart()
{
    return vehiculRowStart;
}

void plateau::setVehiculRowStart(int vehiculRowStart)
{
    vehiculRowStart = vehiculRowStart;
}

int plateau::getVehiculColStart()
{
    return vehiculColStart;
}

void plateau::setVehiculColStart(int vehiculColStart)
{
    vehiculColStart = vehiculColStart;
}

int plateau::getVehicleLength()
{
    return VehicleLength;
}

void plateau::setVehicleLength(int VehicleLength)
{
    VehicleLength = VehicleLength;
}

bool plateau::getVehiculDirection()
{
    return vehiculDirection;
}

void plateau::setVehiculDirection(bool vehiculDirection)
{
    vehiculDirection = vehiculDirection;
}

vector<vehicule> plateau::getVehicules()
{
    return vehicules;
}

char plateau::getBoard(int row, int col)
{
    return board[row][col];
}