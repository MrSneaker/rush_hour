#include "Affichage.hpp"

Affichage::Affichage(plateau p)
{
    window = NULL;
    renderer = NULL;
    texture = NULL;
    surface = NULL;
    font = NULL;
    this->p = p;
}

Affichage::~Affichage()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Affiche du texte selon l'entrée
void Affichage::AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a)
{

    // return;
    SDL_Color color = {r, g, b};
    const char *text = Msg.c_str(); // convertir string en char

    if (Msg == "")
    {
        ostringstream Val;                      // convertir float en string
        Val << Valeur;                          //
        string val = MsgWithValeur + Val.str(); // concatener les deux strings
        text = val.c_str();
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_SetSurfaceAlphaMod(surface, a);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int w = w;
    int h = h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dstrect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Affichage::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << "Erreur d'initialisation de la SDL : " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur d'initialisation de SDL_ttf : " << TTF_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("RushHour", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Erreur de creation de la fenetre : " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "Erreur de creation du renderer : " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("data/arial.ttf", 24);
    if (font == NULL)
    {
        cout << "Erreur de chargement de la police : " << TTF_GetError() << endl;
        exit(EXIT_FAILURE);
    }
}

void Affichage::display()
{
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_DOWN:
                    p.moveVehicule(p.getVehicules()[2], true, 1, 1);
                    break;
                case SDLK_UP:
                    p.moveVehicule(p.getVehicules()[2], false, 1, 1);
                    break;
                }

            default:
                break;
            }
        }
        displayBoard();
    }
}

void Affichage::displayMenu()
{
    // TODO
}

void Affichage::displayBoard()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // quadrillage 6x6
    for (int i = 0; i < HEIGHT; i += HEIGHT / 6)
    {
        SDL_RenderDrawLine(renderer, 0, i, WIDTH, i);
        SDL_RenderDrawLine(renderer, i, 0, i, HEIGHT);
    }

    // TODO : afficher les voitures :
    // - récupérer les voitures du plateau
    // - récupérer les coordonnées de chaque voiture
    // - afficher les voitures

    for (int i = 0; i < p.getVehicules().size(); i++)
    {

        SDL_Rect rect;
        rect.x = p.getVehicules()[i].getPositionCol() * (WIDTH / 6) + 10;
        rect.y = p.getVehicules()[i].getPositionRow() * (HEIGHT / 6) + 10;
        if (p.getVehicules()[i].getDirection() == 0)
        {
            rect.w = (WIDTH / 6) - 20;
            rect.h = (HEIGHT / 6) * p.getVehicules()[i].getLength() - 20;
        }
        else
        {
            rect.w = (WIDTH / 6) * p.getVehicules()[i].getLength() - 20;
            rect.h = (HEIGHT / 6) - 20;
        }

        SDL_SetRenderDrawColor(renderer, p.getVehicules()[i].r, p.getVehicules()[i].g, p.getVehicules()[i].b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // ecrit le numero de la voiture au milieu de la voiture
        AfficherTexte(font, "", "", i, rect.x + rect.w / 2 - 10, rect.y + rect.h / 2 - 10, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
}
