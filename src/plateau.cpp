#include "plateau.h"
#include <assert.h>

plateau::plateau()
{
    initBoard();
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
                cout << "\033[0m";
            cout << board[i][j] << "      ";
        }
        cout << endl
             << endl
             << endl;
    }
    cout << "-------------------------------------------" << endl
         << endl;
}

void plateau::moveVehicule(vehicule &v, bool dir)
{
    bool ok_to_go = false;
    if (dir)
    {
        if (v.getDirection())
            ok_to_go = board[v.getPositionRow()][v.getPositionCol() + v.getLength()] == '.';
        else
            ok_to_go = board[v.getPositionRow() + v.getLength()][v.getPositionCol()] == '.';

        if (ok_to_go)
        {
            v.moveForwardToDir();
            // moveCount++;
        }
    }
    else
    {
        if (v.getDirection())
            ok_to_go = board[v.getPositionRow()][v.getPositionCol() - 1] == '.';
        else
            ok_to_go = board[v.getPositionRow() - 1][v.getPositionCol()] == '.';

        if (ok_to_go)
        {
            v.moveBackwardToDir();
            // moveCount++;
        }
    }
    cout << "Move count: " << moveCount << endl;
}

void plateau::play()
{
    moveVehicule(vehicules[1], false);
    displayBoard();
    moveVehicule(vehicules[1], true);
    displayBoard();
    moveVehicule(vehicules[1], true);
    displayBoard();
    moveVehicule(vehicules[1], true);
    displayBoard();
    moveVehicule(vehicules[1], false);
    displayBoard();
}

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