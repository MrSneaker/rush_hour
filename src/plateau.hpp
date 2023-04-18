#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#define TAILLE 6

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "vehicule.hpp"

using namespace std;

struct board_state_struct
{
    bool board_state[TAILLE][TAILLE];
};

class plateau
{

private:
    int size;
    vector<vehicule> vehicules;
    char board[TAILLE][TAILLE];

    // tableau de booléen, case à true si occupée, false sinon.
    board_state_struct states;

    int exitRow;
    int exitCol;
    int vehiculRowStart, vehiculColStart, VehicleLength;

    // nombre de mouvement entre la situation de départ et la situation
    // finale.
    int moveCount;

    // true = horizontal, false = vertical
    bool vehiculDirection;

    // complexité du plateau.
    int finalComplexity;

public:
    plateau();

    // constructeur par fichier
    plateau(string filename);

    // constructeur par copie
    plateau(const plateau &p);

    ~plateau();

    // procédure de reset des valeurs du plateau.
    void reset();

    // procédure d'initialisation du plateau selon le fichier en paramètre.
    void initBoard(string filename);

    // update le plateau par rapport aux mouvements/ajouts réalisées.
    void updateBoard();

    // affichage console du plateau
    void displayBoard() const;

    /*! \brief bouge le vehicule dans la direction indiquée en paramètre si c'est possible.*/
    /*! \param dir true pour avancer false pour reculer*/
    /*! \param pas entier désignant le nombre de case parcouru lors du déplacement*/
    /*! \param effective bool permettant de réaliser un mouvement effectif ou juste un test*/
    bool moveVehicule(vehicule &v, bool dir, int pas, bool effective);

    // fonction auxiliaire de moveVehicule, réalisant un mouvement de pas vers l'avant.
    // renvoie true si le mouvement à bien été réalisé.
    bool moveVehiculeF(vehicule &v, int pas, bool effective);

    // fonction auxiliaire de moveVehicule, réalisant un mouvement de pas vers l'arrière.
    // renvoie true si le mouvement à bien été réalisé.
    bool moveVehiculeB(vehicule &v, int pas, bool effective);

    // fonction renvoyant true si le plateau est une situation gagnante.
    bool win_board() const;

    /* Getters et Setters */
    const int &getSize() const;

    int getExitRow();
    void setExitRow(int exitRow);

    int getExitCol();
    void setExitCol(int exitCol);

    int getVehiculRowStart();
    void setVehiculRowStart(int vehiculRowStart);

    int getVehiculColStart();
    void setVehiculColStart(int vehiculColStart);

    int getVehicleLength();
    void setVehicleLength(int VehicleLength);

    const int &getMoveCount() const;
    void setMoveCount(int moveCount);

    bool getVehiculDirection();
    void setVehiculDirection(bool vehiculDirection);

    const int &getFinalComplexity();
    void setFinalComplexity(int finalComplexity);

    vector<vehicule> &getVehicules();
    void setVehicules(vector<vehicule> vehicules);
    const board_state_struct &getBoardState() const;
    bool operator==(const plateau &p2) const;
    const char &getBoard(int row, int col) const;

    void test_regression();
};

#endif