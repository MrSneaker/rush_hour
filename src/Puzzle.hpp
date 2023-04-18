#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "plateau.hpp"
#include "Graphe.hpp"
#include "vehicule.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <random>
#include <future>
#include <assert.h>

using namespace std;

class Puzzle
{
private:
    int complexite;

public:
    Puzzle();
    plateau p;
    ~Puzzle();

    vehicule randomVehicule(int row, int col);
    /**
     * @brief Place un véhicule sur le plateau ( push_back dans le vecteur de véhicule du plateau )
     *
     * @param v vehicule à placer
     */
    void placeVehicule(vehicule v);
    /**
     * @brief regarde si le véhicule peut être placé sur le plateau
     * ( plusieurs règle comme vehicule hors du plateau, véhicule qui chevauche un autre véhicule, véhicule qui sort du plateau, etc... )
     * @param v véhicule à placer
     * @return true si le véhicule peut être placé
     */
    bool isValidPlacement(vehicule &v);
    /**
     * @brief génère un puzzle aléatoire
     *
     * @param createPuzzlePromise promesse de création du puzzle
     * @return true si le puzzle a été généré
     */
    bool generateRandomPuzzle(std::promise<void> createPuzzlePromise);
    /**
     * @brief sauvagarde le puzzle dans un fichier texte
     *
     * @param filename nom du fichier
     * @return true si le puzzle a été sauvegardé
     */
    bool writePuzzle(string filename);
    void test_regression();
    int getComplexite();
};

#endif