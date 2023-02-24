#include "vehicule.h"


vehicule::vehicule(int longueur, int positionCol, int positionRow, bool orientation){
    this->length = longueur;
    this->positionCol = positionCol;
    this->positionRow = positionRow;
    this->direction = orientation;
}

vehicule::~vehicule(){
}

int vehicule::getLength(){
    return this->length;
}

void vehicule::setLength(int longueur){
    this->length = longueur;
}

int vehicule::getPositionCol(){
    return this->positionCol;
}

void vehicule::setPositionCol(int positionCol){
    this->positionCol = positionCol;
}

int vehicule::getPositionRow(){
    return this->positionRow;
}

void vehicule::setPositionRow(int positionRow){
    this->positionRow = positionRow;
}

bool vehicule::getDirection(){
    return this->direction;
}

void vehicule::setDirection(bool orientation){
    this->direction = orientation;
}


