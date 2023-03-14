#include "plateau.hpp"
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

plateau::plateau(vector<vehicule> vehicules, int exitRow, int exitCol, int vehiculRowStart, int vehiculColStart, int VehicleLength, bool vehiculDirection, int moveCount)
{
    this->vehicules = vehicules;
    this->exitRow = exitRow;
    this->exitCol = exitCol;
    this->vehiculRowStart = vehiculRowStart;
    this->vehiculColStart = vehiculColStart;
    this->VehicleLength = VehicleLength;
    this->vehiculDirection = vehiculDirection;
    this->moveCount = moveCount;
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
    board_state_struct b;
    cout << endl;

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            board[i][j] = '.';
            states.board_state[i][j] = false;
        }
    }

    board[exitRow][exitCol] = 'E';
    states.board_state[exitRow][exitCol] = false;
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

bool plateau::moveVehiculeF(vehicule &v, int pas, bool effective)
{
    bool ok_to_go;
    for (int j = 0; j < vehicules.size(); j++)
    {
        if (v.getDirection())
        {
            // vérifie qu'il n'y ai pas collision entre la position de tête du vehicule[j] et la position future voulue par v.
            // la position de tête correspond à la position sans prise en compte de la longueur.
            // = 1 si libre, 0 sinon.
            bool front_not_free = ((v.getPositionCol() + (v.getLength() - 1) + pas >= vehicules[j].getPositionCol()) &&
                                   (v.getPositionRow() >= vehicules[j].getPositionRow()));
            // même chose mais en prenant en compte la longueur.
            bool back_not_free = ((v.getPositionCol() + (v.getLength() - 1) + pas <= vehicules[j].getPositionCol() + (vehicules[j].getLength() - 1)) &&
                                  (v.getPositionRow() <= vehicules[j].getPositionRow() + (vehicules[j].getLength() - 1)));
            bool cell_taken = front_not_free && back_not_free;

            // test si on est dans le cadre ou non.
            bool in_board = (v.getPositionCol() + (v.getLength() - 1) + pas < TAILLE);
            ok_to_go = !cell_taken && in_board;
        }
        else
        {
            // même chose que le 1er cas, seul la direction traité change.
            bool front_not_free = ((v.getPositionRow() + (v.getLength() - 1) + pas >= vehicules[j].getPositionRow()) &&
                                   (v.getPositionCol() >= vehicules[j].getPositionCol()));
            bool back_not_free = ((v.getPositionRow() + (v.getLength() - 1) + pas <= vehicules[j].getPositionRow() + (vehicules[j].getLength() - 1)) &&
                                  (v.getPositionCol() <= vehicules[j].getPositionCol() + (vehicules[j].getLength() - 1)));
            bool cell_taken = front_not_free && back_not_free;

            bool in_board = (v.getPositionRow() + (v.getLength() - 1) + pas < TAILLE);
            ok_to_go = !cell_taken && in_board;
        }
        if (!ok_to_go)
            break;
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
    // int l = v.getPositionRow();
    // int c = v.getPositionCol();
    // if (v.getDirection()) // horizontal
    // {
    //     c -= 1;
    //     while (c >= c - pas)
    //     {
    //         c -= 1;
    //     }
    // }
    // else // vertical
    // {
    //     l -= pas;
    // }

    for (int j = 0; j < vehicules.size(); j++)
    {
        if (v.getDirection())
        {
            bool front_not_free = ((v.getPositionCol() - pas >= vehicules[j].getPositionCol()) &&
                                   (v.getPositionRow() >= vehicules[j].getPositionRow()));
            bool back_not_free = ((v.getPositionCol() - pas <= vehicules[j].getPositionCol() + (vehicules[j].getLength() - 1)) &&
                                  (v.getPositionRow() <= vehicules[j].getPositionRow() + (vehicules[j].getLength() - 1)));
            bool cell_taken = front_not_free && back_not_free;

            bool in_board = (v.getPositionCol() - pas > 0);
            ok_to_go = !cell_taken && in_board;
        }
        else
        {
            bool front_not_free = ((v.getPositionRow() - pas >= vehicules[j].getPositionRow()) &&
                                   (v.getPositionCol() >= vehicules[j].getPositionCol()));
            bool back_not_free = ((v.getPositionRow() - pas <= vehicules[j].getPositionRow() + (vehicules[j].getLength() - 1)) &&
                                  (v.getPositionCol() <= vehicules[j].getPositionCol() + (vehicules[j].getLength() - 1)));
            bool cell_taken = front_not_free && back_not_free;

            bool in_board = (v.getPositionRow() - pas > 0);
            ok_to_go = !cell_taken && in_board;
        }
        if (!ok_to_go)
            break;
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
    cout << "Move count: " << moveCount << endl;
    return move_ok;
}

void plateau::play()
{
    moveVehicule(vehicules[1], false, 1, true);
    displayBoard();
    moveVehicule(vehicules[1], true, 2, true);
    displayBoard();
    moveVehicule(vehicules[6], true, 1, true);
    displayBoard();
    moveVehicule(vehicules[6], true, 1, true);
    displayBoard();
    moveVehicule(vehicules[6], false, 1, true);
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

vector<vehicule> &plateau::getVehicules()
{
    return vehicules;
}

void plateau::setVehicules(vector<vehicule> vehicules)
{
    this->vehicules = vehicules;
}

board_state_struct plateau::getBoardState()
{
    return states;
}

char plateau::getBoard(int row, int col)
{
    return board[row][col];
}

int plateau::getMoveCount()
{
    return moveCount;
}