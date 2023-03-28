#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include "plateau.hpp"
#include "Graphe.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
    bool isPressed;
    int BoardNumber;
    int YClicked, XClicked;
    int Ymotion, Xmotion;

public:
    Affichage();
    ~Affichage();

    void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);

    void init();
    void loadDisplay();
    int display();
    bool displayBoard(State s);
    bool displayMenuBar(int BoardNumber);
    int displayMenu();
};

#endif
