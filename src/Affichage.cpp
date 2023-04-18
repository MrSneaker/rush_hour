#include "Affichage.hpp"

Affichage::Affichage()
{
    window = NULL;
    renderer = NULL;
    texture = NULL;
    surface = NULL;
    font = NULL;

    b_playX = WIDTH / 2 - 130;
    b_playY = 60;
    b_playW = 260;
    b_playH = 50;

    puzzleChosenX = WIDTH / 2 - 225;
    puzzleChosenY = b_playY + b_playH + space;
    puzzleChosenW = 450;
    puzzleChosenH = 450;

    caretRightX = WIDTH / 2 + 225 + 50;
    caretRightY = 312;
    caretRightW = 50;
    caretRightH = 100;

    caretLeftX = WIDTH / 2 - 225 - 100;
    caretLeftY = 312;
    caretLeftW = 50;
    caretLeftH = 100;

    b_createNewX = WIDTH / 2 - 210;
    b_createNewY = puzzleChosenY + puzzleChosenH + space + 33 + space + 33 + space;
    b_createNewW = 420;
    b_createNewH = 50;

    b_quitX = WIDTH / 2 - 130;
    b_quitY = b_createNewY + b_createNewH + space;
    b_quitW = 260;
    b_quitH = 50;

    currentBoard.initBoard("data/puzzlesTXT/puzzle" + to_string(currentPuzzleNumber) + ".txt");
    currentBoardComplexity = currentBoard.getFinalComplexity();

    getPuzzleNumberMax();
}

// fonction qui récupère le nombre de puzzle dans le dossier "Puzzles" et le stocke dans puzzleNumberMax
void Affichage::getPuzzleNumberMax()
{
    int index = 1;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("data/puzzlesTXT")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.')
            {
                index++;
            }
        }
        closedir(dir);
        puzzleNumberMax = index - 1;
        // cout << "value puzzleNumberMax = " << puzzleNumberMax << endl;
    }
    else
    {
        perror("Erreur d'ouverture du dossier");
    }
}

Affichage::~Affichage()
{
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    caretRight.~Image();
    caretLeft.~Image();
    puzzleChosen.~Image();

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

    caretRight.loadFromFile("data/caret-right-solid.png", renderer);
    caretLeft.loadFromFile("data/caret-left-solid.png", renderer);
    loadingIcon.loadFromFile("data/loadingIcon.png", renderer);
}

void Affichage::updateCaretDimensions(unsigned int &x, unsigned int &y, unsigned int &w, unsigned int &h, int xMotion, int yMotion, int xOffset, string side)
{
    if (xMotion >= x && xMotion <= x + w && yMotion >= y && yMotion <= y + h)
    {
        w = 53;
        h = 103;
        if (side == "right")
            x = WIDTH / 2 + 225 + xOffset - 3;
        else
            x = WIDTH / 2 - 225 - xOffset;
        y = 311;
    }
    else
    {
        w = 50;
        h = 100;
        if (side == "right")
            x = WIDTH / 2 + 225 + xOffset - 1;
        else
            x = WIDTH / 2 - 225 - xOffset + 1;
        y = 312;
    }
}

void Affichage::updateButtonDimensions(int &x, int &y, int &w, int &h, int xMotion, int yMotion, int xOffset, int yOffset, string which)
{

    if (xMotion >= x && xMotion <= x + w && yMotion >= y && yMotion <= y + h)
    {
        if (which == "Solve" || which == "quit")
        {
            x = WIDTH / 2 - 130;
            y = which == "Solve" ? 60 - yOffset / 2 : b_createNewY + b_createNewH + space - yOffset / 2;
            w = 260 + xOffset / 2;
            h = 50 + yOffset / 2;
        }
        else
        {
            x = WIDTH / 2 - 210;
            y = puzzleChosenY + 450 + space + 33 + space + 33 + space - yOffset / 2;
            w = 420 + xOffset / 2;
            h = 50 + yOffset / 2;
        }
    }
    else
    {
        if (which == "Solve" || which == "quit")
        {
            x = WIDTH / 2 - 130;
            y = which == "Solve" ? 60 : puzzleChosenY + puzzleChosenH + space + 33 + space + 33 + space + 50 + space;
            w = 260;
            h = 50;
        }
        else
        {
            x = WIDTH / 2 - 210;
            y = puzzleChosenY + 450 + space + 33 + space + 33 + space;
            w = 420;
            h = 50;
        }
    }
}

void Affichage::displayPuzzleChosen()
{
    State s;
    s.setBoard(currentBoard);

    // quadrillage 6x6
    // à partir de x = puzzleChosenX et y = puzzleChosenY
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < 6; i++)
    {
        SDL_RenderDrawLine(renderer, puzzleChosenX + (i * (450 / 6)), puzzleChosenY, puzzleChosenX + (i * (450 / 6)), puzzleChosenY + 450);
        SDL_RenderDrawLine(renderer, puzzleChosenX, puzzleChosenY + (i * (450 / 6)), puzzleChosenX + 450, puzzleChosenY + (i * (450 / 6)));
    }

    int i = 0;
    for (const auto &voiture : s.getBoard_aff().getVehicules())
    {
        // prend en compte l'inclinaison de la voiture
        SDL_Rect rect;
        rect.x = voiture.getPositionCol() * (450 / 6) + puzzleChosenX + 10;
        rect.y = voiture.getPositionRow() * (450 / 6) + puzzleChosenY + 10;
        if (voiture.getDirection() != 0)
        {
            rect.w = voiture.getLength() * (450 / 6) - 20;
            rect.h = (450 / 6) - 20;
        }
        else
        {
            rect.w = (450 / 6) - 20;
            rect.h = voiture.getLength() * (450 / 6) - 20;
        }

        SDL_SetRenderDrawColor(renderer, voiture.r, voiture.g, voiture.b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // affiche le numéro de la voiture
        if (voiture.getDirection() != 0)
            // Horizontal
            if (i > 9)
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 12, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
            else
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 5, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
        else
            // Vertical
            if (i > 9)
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 12, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
            else
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 5, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }

        i++;
    }
}

void Affichage::createNewPuzzle(std::promise<void> createPuzzlePromise)
{
    cout << "--------------------------- Creating a new puzzle... ---------------------------" << endl;
    Puzzle puzzle;

    auto start = chrono::high_resolution_clock::now();
    queueCreation.push_back(false);
    puzzle.generateRandomPuzzle(std::move(createPuzzlePromise)); // genere un nouveau puzzle aleatoire avec la promesse createPuzzlePromise
    auto stop = chrono::high_resolution_clock::now();
    queueCreation.pop_back();

    chrono::duration<double> duration = stop - start;
    float createTime = std::round(duration.count() * 100) / 100;

    cout << "Puzzle created in " << createTime << " seconds" << endl;

    puzzle.writePuzzle("./data/puzzlesTXT/puzzle" + to_string(puzzleNumberMax + 1) + ".txt"); // Écrit le puzzle dans un nouveau fichier

    cout << "New puzzle successfully created at : "
         << "./data/puzzlesTXT/puzzle" + to_string(puzzleNumberMax + 1) + ".txt" << endl;

    getPuzzleNumberMax();                                                                     // Met à jour le nombre de puzzles disponibles
    currentBoard.initBoard("./data/puzzlesTXT/puzzle" + to_string(puzzleNumberMax) + ".txt"); // Charge le fichier du dernier puzzle créé

    cout << "--------------------------- New puzzle created ! ---------------------------" << endl;

    currentPuzzleNumber = puzzleNumberMax;                      // Met à jour le numéro de puzzle en cours
    currentBoardComplexity = currentBoard.getFinalComplexity(); // Met à jour la complexité du puzzle en cours
}

int Affichage::displayMenu()
{

    // Initialisation des éléments du menu
    SDL_Rect playButton;
    SDL_Rect createButton;
    SDL_Rect quitButton;

    bool displayMenu = true;

    while (displayMenu)
    {

        playButton = {b_playX, b_playY, b_playW, b_playH};
        createButton = {b_createNewX, b_createNewY, b_createNewW, b_createNewH};
        quitButton = {b_quitX, b_quitY, b_quitW, b_quitH};

        // Affichage des Elements du menu
        // Bouttons
        SDL_SetRenderDrawColor(renderer, 127, 67, 229, 255);
        SDL_RenderFillRect(renderer, &playButton);
        AfficherTexte(font, "Solve", "", 0, b_playX + 98, b_playY + 10, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &createButton);
        AfficherTexte(font, "Create new puzzle", "", 0, b_createNewX + 110, b_createNewY + 10, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &quitButton);
        AfficherTexte(font, "Quit", "", 0, b_quitX + 110, b_quitY + 10, 255, 255, 255, 255);

        // ajoute une petit effet d'ombre aux bouttons, en bas à gauche
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderDrawLine(renderer, playButton.x + 1, playButton.y + playButton.h, playButton.x + playButton.w, playButton.y + playButton.h);
        SDL_RenderDrawLine(renderer, playButton.x + playButton.w, playButton.y + 1, playButton.x + playButton.w, playButton.y + playButton.h);
        SDL_RenderDrawLine(renderer, createButton.x + 1, createButton.y + createButton.h, createButton.x + createButton.w, createButton.y + createButton.h);
        SDL_RenderDrawLine(renderer, createButton.x + createButton.w, createButton.y + 1, createButton.x + createButton.w, createButton.y + createButton.h);
        SDL_RenderDrawLine(renderer, quitButton.x + 1, quitButton.y + quitButton.h, quitButton.x + quitButton.w, quitButton.y + quitButton.h);
        SDL_RenderDrawLine(renderer, quitButton.x + quitButton.w, quitButton.y + 1, quitButton.x + quitButton.w, quitButton.y + quitButton.h);

        // ajout une bordure de 2px aux slider
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderDrawLine(renderer, puzzleChosenX - 1, puzzleChosenY - 1, puzzleChosenX + puzzleChosenW + 1, puzzleChosenY - 1);
        SDL_RenderDrawLine(renderer, puzzleChosenX - 1, puzzleChosenY - 1, puzzleChosenX - 1, puzzleChosenY + puzzleChosenH + 1);
        SDL_RenderDrawLine(renderer, puzzleChosenX + puzzleChosenW + 1, puzzleChosenY - 1, puzzleChosenX + puzzleChosenW + 1, puzzleChosenY + puzzleChosenH + 1);
        SDL_RenderDrawLine(renderer, puzzleChosenX - 1, puzzleChosenY + puzzleChosenH + 1, puzzleChosenX + puzzleChosenW + 1, puzzleChosenY + puzzleChosenH + 1);
        SDL_RenderDrawLine(renderer, puzzleChosenX - 2, puzzleChosenY - 2, puzzleChosenX + puzzleChosenW + 2, puzzleChosenY - 2);
        SDL_RenderDrawLine(renderer, puzzleChosenX - 2, puzzleChosenY - 2, puzzleChosenX - 2, puzzleChosenY + puzzleChosenH + 2);
        SDL_RenderDrawLine(renderer, puzzleChosenX + puzzleChosenW + 2, puzzleChosenY - 2, puzzleChosenX + puzzleChosenW + 2, puzzleChosenY + puzzleChosenH + 2);
        SDL_RenderDrawLine(renderer, puzzleChosenX - 2, puzzleChosenY + puzzleChosenH + 2, puzzleChosenX + puzzleChosenW + 2, puzzleChosenY + puzzleChosenH + 2);

        // slider
        displayPuzzleChosen();
        caretLeft.draw(renderer, caretLeftX, caretLeftY, caretLeftW, caretLeftH);
        caretRight.draw(renderer, caretRightX, caretRightY, caretRightW, caretRightH);

        // Affichage du numéro du puzzle
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        AfficherTexte(font, "Puzzle number : ", "", 0, WIDTH / 2 - 78, puzzleChosenY + puzzleChosenH + space, 0, 0, 0, 255);
        AfficherTexte(font, "", "", currentPuzzleNumber, WIDTH / 2 + 102, puzzleChosenY + puzzleChosenH + space, 0, 0, 0, 255);

        // Affichage de la complexité du puzzle
        AfficherTexte(font, "Complexity : ", "", 0, WIDTH / 2 - 78, puzzleChosenY + puzzleChosenH + space + 30, 0, 0, 0, 255);
        AfficherTexte(font, "", "", currentBoardComplexity, WIDTH / 2 + 60, puzzleChosenY + puzzleChosenH + space + 30, 0, 0, 0, 255);

        SDL_SetRenderDrawColor(renderer, 216, 223, 227, 255);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                displayMenu = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    displayMenu = false;
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
        // hover
        updateCaretDimensions(caretLeftX, caretLeftY, caretLeftW, caretLeftH, Xmotion, Ymotion, 102, "left");
        updateCaretDimensions(caretRightX, caretRightY, caretRightW, caretRightH, Xmotion, Ymotion, 49, "right");

        updateButtonDimensions(b_playX, b_playY, b_playW, b_playH, Xmotion, Ymotion, 4, 4, "Solve");
        updateButtonDimensions(b_createNewX, b_createNewY, b_createNewW, b_createNewH, Xmotion, Ymotion, 4, 4, "create");
        updateButtonDimensions(b_quitX, b_quitY, b_quitW, b_quitH, Xmotion, Ymotion, 4, 4, "quit");

        // Vérifie si un bouton de la souris a été pressé
        if (isPressed)
        {
            // Vérifie si le bouton de déplacement à gauche a été cliqué
            if (XClicked >= caretLeftX && XClicked <= caretLeftX + caretLeftW &&
                YClicked >= caretLeftY && YClicked <= caretLeftY + caretLeftH)
            {
                // Vérifie si le numéro de puzzle actuel est supérieur à 1
                if (currentPuzzleNumber > 1)
                {
                    --currentPuzzleNumber;                                                                        // Décrémente le numéro de puzzle
                    currentBoard.initBoard("./data/puzzlesTXT/puzzle" + to_string(currentPuzzleNumber) + ".txt"); // Charge le fichier de puzzle correspondant
                    currentBoardComplexity = currentBoard.getFinalComplexity();
                }

                // Vérifie si le bouton de déplacement à droite a été cliqué
            }
            else if (XClicked >= caretRightX && XClicked <= caretRightX + caretRightW &&
                     YClicked >= caretRightY && YClicked <= caretRightY + caretRightH)
            {
                // Vérifie si le numéro de puzzle actuel est inférieur au maximum autorisé
                if (currentPuzzleNumber < puzzleNumberMax)
                {
                    ++currentPuzzleNumber;                                                                        // Incrémente le numéro de puzzle
                    currentBoard.initBoard("./data/puzzlesTXT/puzzle" + to_string(currentPuzzleNumber) + ".txt"); // Charge le fichier de puzzle correspondant
                    currentBoardComplexity = currentBoard.getFinalComplexity();
                }
            }

            // Vérifie si le bouton de lecture a été cliqué
            else if (XClicked >= playButton.x && XClicked <= playButton.x + playButton.w &&
                     YClicked >= playButton.y && YClicked <= playButton.y + playButton.h)
            {
                cout << "file : "
                     << "./data/puzzlesTXT/puzzle" + to_string(currentPuzzleNumber) + ".txt" << endl;
                currentBoard.initBoard("./data/puzzlesTXT/puzzle" + to_string(currentPuzzleNumber) + ".txt"); // Charge le fichier de puzzle correspondant
                return 1;                                                                                     // Retourne 1 pour indiquer que le jeu doit être lancé
            }
            // Vérifie si le bouton de création a été cliqué
            else if (XClicked >= createButton.x && XClicked <= createButton.x + createButton.w &&
                     YClicked >= createButton.y && YClicked <= createButton.y + createButton.h)
            {
                std::promise<void> createPuzzlePromise;                                  // Création d'une promesse
                std::future<void> createPuzzleFuture = createPuzzlePromise.get_future(); // Création d'un futur

                /* Création d'un thread qui va créer un nouveau puzzle
                    et qui va attendre la promesse pour continuer, on utilise std::move pour
                    déplacer la promesse et éviter une copie et mutable pour pouvoir modifier la promesse */
                std::thread createPuzzleThread([this, createPuzzlePromise = std::move(createPuzzlePromise)]() mutable
                                               { createNewPuzzle(std::move(createPuzzlePromise)); });

                createPuzzleThread.detach(); // Détache le thread de l'application pour qu'il puisse continuer à tourner en arrière plan
            }
            // Vérifie si le bouton de sortie
            else if (XClicked >= quitButton.x && XClicked <= quitButton.x + quitButton.w &&
                     YClicked >= quitButton.y && YClicked <= quitButton.y + quitButton.h)
            {
                return -1; // Retourne -1 pour indiquer que le jeu doit être quitté
            }
        }
        if (!queueCreation.empty())
        {

            AfficherTexte(font, "Creating new puzzle :", "", 0, createButton.x + createButton.w / 2 - 108 - 15, createButton.y - 40, 0, 0, 0, 255);
            loadingIcon.draw(renderer, createButton.x + createButton.w / 2 + 108 + 15, createButton.y - 40, 30, 30, angle);
            angle += 10;
        }

        isPressed = false;
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(10);
    }
    return -1;
}

bool Affichage::displayMenuBar(int BoardNumber, float solveTime)
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
    AfficherTexte(font, "Quit", "", 0, 45, HEIGHT - 65, 255, 255, 255, 255);

    // affichage du numéro du board
    AfficherTexte(font, "", "Step : ", BoardNumber, 350, HEIGHT - 65, 0, 0, 0, 255);

    AfficherTexte(font, "Solvetime : ", "", 0, 600, HEIGHT - 65, 0, 0, 0, 255);
    AfficherTexte(font, "", "", solveTime, 720, HEIGHT - 65, 0, 0, 0, 255);
    AfficherTexte(font, "s", "", 0, 770, HEIGHT - 65, 0, 0, 0, 255);

    // si on clique sur le bouton "Quitter"
    if (isPressed && XClicked >= 20 && XClicked <= 120 && YClicked >= HEIGHT - 75 && YClicked <= HEIGHT - 25)
    {
        return false;
    }

    return true;
}

bool Affichage::displayBoard(State s, float solveTime)
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

    int i = 0;
    for (const auto &voiture : s.getBoard_aff().getVehicules())
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
        if (voiture.getDirection() != 0)
            // Horizontal
            if (i > 9)
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 12, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
            else
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 5, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
        else
            // Vertical
            if (i > 9)
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 12, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
            else
            {
                AfficherTexte(font, to_string(i), "", 0, rect.x + rect.w / 2 - 5, rect.y + rect.h / 2 - 13, 255, 255, 255, 255);
            }
        ++i;
    }

    return displayMenuBar(s.getBoard_aff().getMoveCount(), solveTime);
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
    }
}

int Affichage::display()
{
    bool display = true;
    int i = 0;
    Graphe g;
    State s;
    s.setBoard(currentBoard);
    // calcul le temps d'execution de l'algorithme
    auto start = chrono::high_resolution_clock::now();
    g.breadthFirstSearch(s, 100000);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    float solveTime = elapsed.count();
    solveTime = roundf(solveTime * 100) / 100;

    while (display)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    return -1;
                    break;
                case SDLK_LEFT:
                    // on affiche le board précédent dans le chemin
                    if (i > 0)
                    {
                        i--;
                        displayBoard(g.path[i], solveTime);
                    }

                    break;
                case SDLK_RIGHT:
                    // on affiche le board suivant dans le chemin
                    if (i < g.path.size() - 1)
                    {
                        i++;
                        displayBoard(g.path[i], solveTime);
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
        if (!displayBoard(g.path[i], solveTime))
        {
            display = false;
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(10);
    }

    return 0;
}
