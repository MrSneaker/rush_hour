#include "plateau.h"

plateau::plateau(){
    this->initBoard();
}

plateau::~plateau(){
}

void plateau::initBoard(){
    ifstream infile("data/puzzle.txt");
    infile >> this->exitRow >> this->exitCol;
    infile >> this->vehiculRowStart >> this->vehiculColStart >> this->VehicleLength >> this->vehiculDirection;
    int row,col,len,dir;
    while(infile >> row >> col >> len >> dir){
        this->vehicules.push_back(vehicule(len,col,row,dir));
    }
    infile.close();
}

void plateau::displayBoard(){


    for(int i=0; i<TAILLE; i++){
        for(int j=0; j<TAILLE; j++){
            this->board[i][j] = '.';
        }
    }

    board[this->exitRow][this->exitCol] = 'E';

    for(int i=0; i<this->vehicules.size(); i++){
        vehicule v = this->vehicules[i];
        char symbol = i == 0 ? 'X' : 'A'+i-1;
        for(int j=0; j<v.getLength(); j++){
            if(v.getDirection()){
                board[v.getPositionRow()][v.getPositionCol()+j] = symbol;
            } else {
                board[v.getPositionRow()+j][v.getPositionCol()] = symbol;
            }
        }
    }

    for(int i=0; i<TAILLE; i++){
        cout<<i<<"      ";
    }
    cout<<endl<<endl<<endl;

    for(int i=0; i<TAILLE; i++){
        for(int j=0; j<TAILLE; j++){
            if(this->board[i][j] == 'X')
                cout<<"\033[1;31m";
            else if(this->board[i][j] == 'E')
                cout<<"\033[1;32m";
            else
                cout<<"\033[0m";
                cout<<this->board[i][j]<<"      ";

        }
        cout<<endl<<endl;
    }



}