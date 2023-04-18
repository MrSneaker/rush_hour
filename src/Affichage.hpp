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
    vector<plateau> boards;
    int currentBoardComplexity;
    bool isPressed;
    int BoardNumber;
    int YClicked, XClicked;
    int Ymotion, Xmotion;
    SDL_Cursor *cursor;
    int space = 27;
    int currentPuzzleNumber = 1;
    int puzzleNumberMax = 0;
    vector<bool> queueCreation;
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

    void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);

    void init();
    void loadDisplay();
    int display();
    bool displayBoard(State s, float solveTime);
    bool displayMenuBar(int BoardNumber, float solveTime);
    int displayMenu();
    void displayPuzzleChosen();
    void createNewPuzzle(std::promise<void> createPuzzlePromise);
    void getPuzzleNumberMax();
    void updateCaretDimensions(unsigned int &x, unsigned int &y, unsigned int &w, unsigned int &h, int xMotion, int yMotion, int xOffset, string side);
    void updateButtonDimensions(int &x, int &y, int &w, int &h, int xMotion, int yMotion, int xOffset, int yOffset, string which);
};

#endif
