#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include "plateau.hpp"
#include "Graphe.hpp"
#include "Image.hpp"
#include "Puzzle.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <dirent.h>
#include <thread>
#include <future>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 800
#define HEIGHT 900

using namespace std;

class Affichage
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Event event;
    TTF_Font *font;

    Graphe g;
    plateau currentBoard;

    vector<bool> queueCreation;
    vector<int> puzzleTab;

    int currentBoardComplexity; 
    bool isPressed;
    int YClicked, XClicked;
    int Ymotion, Xmotion;
    int space = 27;
    int currentPuzzleNumber = 1;
    int puzzleNumberMax = 0;
    int angle = 0;

    //-----------------Image-----------------

    Image caretRight;
    unsigned int caretRightX;
    unsigned int caretRightY;
    unsigned int caretRightW;
    unsigned int caretRightH;

    Image caretLeft;
    unsigned int caretLeftX;
    unsigned int caretLeftY;
    unsigned int caretLeftW;
    unsigned int caretLeftH;

    Image puzzleChosen;
    unsigned int puzzleChosenX;
    unsigned int puzzleChosenY;
    unsigned int puzzleChosenW;
    unsigned int puzzleChosenH;

    Image loadingIcon;
    unsigned int loadingIconX;
    unsigned int loadingIconY;
    unsigned int loadingIconW;
    unsigned int loadingIconH;

    //-----------------Boutons-----------------
    int b_playX;
    int b_playY;
    int b_playW;
    int b_playH;

    int b_quitX;
    int b_quitY;
    int b_quitW;
    int b_quitH;

    int b_createNewX;
    int b_createNewY;
    int b_createNewW;
    int b_createNewH;

public:
    Affichage();
    ~Affichage();

    /**
     * @brief permet d'afficher un texte selon le type d'entrée.
     Pour afficher un texte avec une valeur, il faut mettre Msg à "" et MsgWithValeur à "[ texte à afficher ] et la valeur est : [valeur]" et inversement
     * @param font la police d'écriture
     * @param Msg le message à afficher (sans valeur)
     * @param MsgWithValeur le message à afficher (avec valeur)
     * @param Valeur la valeur à afficher
     * @param x la position en x
     * @param y la position en y
     * @param r la couleur rouge
     * @param g la couleur verte
     * @param b la couleur bleue
     * @param a la transparence
     */
    void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);

    void init();
    /**
     * @brief gère l'échange de fenêtre
     */
    void loadDisplay();
    /**
     * @brief affichage de la fenêtre de solution
     */
    int display();
    /**
     * @brief affichage du plateau
     * @param s etat qui contient le plateau
     * @param solveTime le temps de résolution
     * @return false si on cliqué sur le bouton "quitter"
     */
    bool displayBoard(State s, float solveTime);
    /**
     * @brief affichage de la barre de menu dans la fenêtre de solution
     * @param BoardNumber numéro pour indiquer l'avancement du puzzle (nombre de coups joués)
     * @param solveTime le temps de résolution
     * @return false si on cliqué sur le bouton "quitter"
     */
    bool displayMenuBar(int BoardNumber, float solveTime);
    /**
     * @brief affichage de la fenêtre de menu principal
     * @return -1 si on quitte l'application, 1 si on résoud un puzzle
     */
    int displayMenu();
    /**
     * @brief affichage en miniature du plateau choisi dans le menu principal avec le slider
     */
    void displayPuzzleChosen();
    /**
     * @brief appel la création d'un nouveau puzzle
     * @param createPuzzlePromise promesse de création d'un nouveau puzzle
     */
    void createNewPuzzle(std::promise<void> createPuzzlePromise);
    /**
     * @brief récupère le nombre de puzzle dans le dossier "puzzles" et stock les numéros des puzzles dans un tableau
     */
    void getPuzzleNumberMax();
    /**
     * @brief récupère un nouveau numéro de puzzle pour la création d'un nouveau puzzle
     * ( regarde si le numéro est déjà utilisé, si oui, il en prend un autre, sinon il le renvoie )
     * -> permet de ne pas écraser un puzzle déjà existant et de garder un certains ordre
     * @return le numéro de puzzle
     */
    int getNewPuzzleNumber();
    /**
     * @brief permet de faire le hover sur les carets du slider
     * @param x la position en x
     * @param y la position en y
     * @param w la largeur
     * @param h la hauteur
     * @param xMotion la position en x de la souris
     * @param yMotion la position en y de la souris
     * @param xOffset le décalage en x
     * @param side le côté du caret (gauche ou droite)
     */
    void updateCaretDimensions(unsigned int &x, unsigned int &y, unsigned int &w, unsigned int &h, int xMotion, int yMotion, int xOffset, string side);
    /**
     * @brief permet de faire le hover sur les boutons
     * @param x la position en x
     * @param y la position en y
     * @param w la largeur
     * @param h la hauteur
     * @param xMotion la position en x de la souris
     * @param yMotion la position en y de la souris
     * @param xOffset le décalage en x
     * @param yOffset le décalage en y
     * @param which le bouton (play, quit, createNew)
     */
    void updateButtonDimensions(int &x, int &y, int &w, int &h, int xMotion, int yMotion, int xOffset, int yOffset, string which);
};

#endif
