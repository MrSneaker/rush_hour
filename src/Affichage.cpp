#include "Affichage.hpp"

Affichage::Affichage(Graphe g)
{
    window = NULL;
    renderer = NULL;
    texture = NULL;
    surface = NULL;
    font = NULL;
    this->g = g;
}

Affichage::~Affichage()
{
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();

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

int Affichage::displayMenu()
{
    int space = 27;
    // Initialisation des éléments du menu
    SDL_Rect playButton = {WIDTH / 2 - 130, 60, 260, 50};
    SDL_Rect slider = {WIDTH / 2 - 225, playButton.y + playButton.h + space, 450, 450};
    SDL_Rect puzzleNum;        // x : WIDTH / 2 - taille du txt ; y : slider.y + slider.h + space
    SDL_Rect puzzledifficulty; // x : WIDTH / 2 - taille du txt ; y : puzzleNum.y + puzzleNum.h + space
    SDL_Rect createButton = {WIDTH / 2 - 210, slider.y + slider.h + space + 33 + space + 33 + space, 420, 50};
    SDL_Rect quitButton = {WIDTH / 2 - 130, createButton.y + createButton.h + space, 260, 50};
    // TDOO : Ajouter les flèches pour le slider

    // Initialisation des variables
    int puzzleNumber = 1;
    int difficulty = 1;

    bool displayMenu = true;

    while (displayMenu)
    {

        // Affichage du menu blanc

        // Affichage des Elements du menu
        // Bouttons
        SDL_SetRenderDrawColor(renderer, 127, 67, 229, 255);
        SDL_RenderFillRect(renderer, &playButton);
        AfficherTexte(font, "Play", "", 0, WIDTH / 2 - 24, playButton.y + 10, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &createButton);
        AfficherTexte(font, "Create new puzzle", "", 0, WIDTH / 2 - 102, createButton.y + 10, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &quitButton);
        AfficherTexte(font, "Quit", "", 0, WIDTH / 2 - 24, quitButton.y + 10, 255, 255, 255, 255);

        // ajoute une petit effet d'ombre aux bouttons, en bas à gauche
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderDrawLine(renderer, playButton.x + 1, playButton.y + playButton.h, playButton.x + playButton.w, playButton.y + playButton.h);
        SDL_RenderDrawLine(renderer, playButton.x + playButton.w, playButton.y + 1, playButton.x + playButton.w, playButton.y + playButton.h);
        SDL_RenderDrawLine(renderer, createButton.x + 1, createButton.y + createButton.h, createButton.x + createButton.w, createButton.y + createButton.h);
        SDL_RenderDrawLine(renderer, createButton.x + createButton.w, createButton.y + 1, createButton.x + createButton.w, createButton.y + createButton.h);
        SDL_RenderDrawLine(renderer, quitButton.x + 1, quitButton.y + quitButton.h, quitButton.x + quitButton.w, quitButton.y + quitButton.h);
        SDL_RenderDrawLine(renderer, quitButton.x + quitButton.w, quitButton.y + 1, quitButton.x + quitButton.w, quitButton.y + quitButton.h);

        // ajout une bordure de 2px aux slider
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, slider.x - 1, slider.y - 1, slider.x + slider.w - 1, slider.y - 1);
        SDL_RenderDrawLine(renderer, slider.x - 1, slider.y - 1, slider.x - 1, slider.y + slider.h - 1);
        SDL_RenderDrawLine(renderer, slider.x + slider.w, slider.y, slider.x + slider.w, slider.y + slider.h);
        SDL_RenderDrawLine(renderer, slider.x, slider.y + slider.h, slider.x + slider.w, slider.y + slider.h);

        // slider
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &slider);
        // TODO : Afficher les flèches pour le slider

        // Affichage du numéro du puzzle
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        AfficherTexte(font, "Puzzle number : ", "", 0, WIDTH / 2 - 78, slider.y + slider.h + 12, 0, 0, 0, 255);
        AfficherTexte(font, "", "", puzzleNumber, WIDTH / 2 + 102, slider.y + slider.h + 12, 0, 0, 0, 255);
        // Affichage de la difficulté du puzzle
        AfficherTexte(font, "", "Difficulty : ", difficulty, WIDTH / 2 - 78, slider.y + slider.h + 12 + 27, 0, 0, 0, 255);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                displayMenu = false;
                break;
            case SDL_KEYDOWN:
            case SDLK_ESCAPE:
                displayMenu = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    XClicked = event.button.x;
                    YClicked = event.button.y;
                    isPressed = true;
                }
                break;
            case SDL_MOUSEMOTION:
                Xmotion = event.motion.x;
                Ymotion = event.motion.y;
                break;

            default:
                break;
            }
        }

        if (XClicked >= playButton.x && XClicked <= playButton.x + playButton.w && YClicked >= playButton.y && YClicked <= playButton.y + playButton.h)
        {
            return 1;
        }
        else if (XClicked >= createButton.x && XClicked <= createButton.x + createButton.w && YClicked >= createButton.y && YClicked <= createButton.y + createButton.h)
        {
            return 2;
        }
        else if (XClicked >= quitButton.x && XClicked <= quitButton.x + quitButton.w && YClicked >= quitButton.y && YClicked <= quitButton.y + quitButton.h)
        {
            return -1;
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(10);
    }
    return -1;
}

bool Affichage::displayMenuBar(int BoardNumber)
{

    // affichage de la barre de menu qui se trouve en dessous de chaque board
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, HEIGHT - 100, WIDTH, HEIGHT - 100);

    // affichage du bouton "Quitter"
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = 20;
    rect.y = HEIGHT - 75;
    rect.w = 100;
    rect.h = 50;
    SDL_RenderFillRect(renderer, &rect);

    // affichage du texte "Quitter"
    AfficherTexte(font, "Quitter", "", 0, 32, HEIGHT - 65, 255, 255, 255, 255);

    // affichage du numéro du board en noir
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    AfficherTexte(font, "", "Board : ", BoardNumber, 350, HEIGHT - 65, 0, 0, 0, 255);

    // si on clique sur le bouton "Quitter"
    if (isPressed && XClicked >= 20 && XClicked <= 120 && YClicked >= HEIGHT - 75 && YClicked <= HEIGHT - 25)
    {
        return false;
    }

    return true;
}

bool Affichage::displayBoard(State s)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // quadrillage 6x6
    for (int i = 0; i < HEIGHT - 100; i += (HEIGHT - 100) / 6)
    {
        SDL_RenderDrawLine(renderer, 0, i, WIDTH, i);
        SDL_RenderDrawLine(renderer, i, 0, i, HEIGHT - 100);
    }

    // TODO : afficher les voitures :
    // - récupérer les voitures du plateau
    // - récupérer les coordonnées de chaque voiture
    // - afficher les voiture avec la bonne couleur
    int i = 0;
    for (auto voiture : s.getBoard().getVehicules())
    {
        // prend en compte l'inclinaison de la voiture
        SDL_Rect rect;
        rect.x = voiture.getPositionCol() * (WIDTH / 6) + 10;
        rect.y = voiture.getPositionRow() * ((HEIGHT - 100) / 6) + 10;
        if (voiture.getDirection() == 0)
        {
            rect.w = (WIDTH / 6) - 20;
            rect.h = ((HEIGHT - 100) / 6) * voiture.getLength() - 20;
        }
        else
        {
            rect.w = (WIDTH / 6) * voiture.getLength() - 20;
            rect.h = ((HEIGHT - 100) / 6) - 20;
        }
        SDL_SetRenderDrawColor(renderer, voiture.r, voiture.g, voiture.b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // affiche le numéro de la voiture
        AfficherTexte(font, "", "", i, rect.x + rect.w / 2, rect.y + rect.h / 2, 0, 0, 0, 255);
        i++;
    }

    return displayMenuBar(s.getBoard().getMoveCount());
}

// Boucle du jeu
void Affichage::loadDisplay()
{

    init();
    int fenetreOuverte = 0;
    while (fenetreOuverte != -1)
    {
        // // Le menu principale
        fenetreOuverte = displayMenu();
        if (fenetreOuverte == 1)
        {
            fenetreOuverte = display();
        }
        else if (fenetreOuverte == 2)
        {
            // TODO : appel la fonction qui permet de créer un puzzle
        }
    }
}

int Affichage::display()
{
    bool display = true;
    int i = 0;
    plateau p;
    State s;
    s.setBoard(p);
    g.breadthFirstSearch(s);

    while (display)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                display = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    display = false;
                    break;
                case SDLK_LEFT:
                    // on affiche le board précédent dans le chemin
                    if (i > 0)
                    {
                        i--;
                        displayBoard(g.path[i]);
                    }

                    break;
                case SDLK_RIGHT:
                    // on affiche le board suivant dans le chemin
                    if (i < g.path.size() - 1)
                    {
                        i++;
                        displayBoard(g.path[i]);
                    }
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    XClicked = event.button.x;
                    YClicked = event.button.y;
                    isPressed = true;
                }
                break;
            case SDL_MOUSEMOTION:
                Xmotion = event.motion.x;
                Ymotion = event.motion.y;
                break;

            default:
                break;
            }
        }

        if (!displayBoard(g.path[i]))
        {
            display = false;
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(10);
    }

    return -1;
}
