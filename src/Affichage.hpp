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
#define HEIGHT 800

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
    plateau p;

public:
    Affichage(plateau p);
    ~Affichage();

    void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);

    void init();
    void display();
    void displayBoard();
    void displayMenu();
};

#endif
