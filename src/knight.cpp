//Seghetto Davide 2008784

#include "../lib/knight.h"

Knight :: Knight(int x, int y, bool color) {
    position.setX(x);
    position.setY(y);
    white = color;
    c = white ? 'c' : 'C';
}

void Knight :: move(const Position& to, ChessBoard& board) {
    makePossiblePositions(board); //aggiorno le possibili posizioni
    
    if(!isValid(to)) throw new InvalidPosition(); //controllo se la mossa appartiene al vettore di possibili posizioni o meno
    else position = to; //aggiorno la variabile membro
}

void Knight :: makePossiblePositions(ChessBoard& board) {
    possiblePositions.clear();
    //le possibili posizioni del cavallo; controllo che la casella di arrivo non esca dai limiti e che non sia occupata da un pezzo dello stesso colore
    //ho bisogno solo di controllare che la posizione di arrivo non sia occupata da un pezzo dello stesso colore, il tragitto per arrivarci può anche essere
    //bloccato, per le caratteristiche del cavallo
    if(getX() > 1 && getY() > 0) {
        if(isFree(Position(getX() - 2, getY() - 1), board) || alterColorPiece(Position(getX() - 2, getY() - 1), board)) possiblePositions.push_back(Position(getX() - 2, getY() - 1));
    }
    if(getX() > 1 && getY() < 7) {
        if(isFree(Position(getX() - 2, getY() + 1), board) || alterColorPiece(Position(getX() - 2, getY() + 1), board)) possiblePositions.push_back(Position(getX() - 2, getY() + 1));
    }
    if(getX() < 6 && getY() > 0) {
        if(isFree(Position(getX() + 2, getY() - 1), board) || alterColorPiece(Position(getX() + 2, getY() - 1), board)) possiblePositions.push_back(Position(getX() + 2, getY() - 1));
    }
    if(getX() < 6 && getY() < 7) {
        if(isFree(Position(getX() + 2, getY() + 1), board) || alterColorPiece(Position(getX() + 2, getY() + 1), board)) possiblePositions.push_back(Position(getX() + 2, getY() + 1));
    }
    if(getX() > 0 && getY() > 1) {
        if(isFree(Position(getX() - 1, getY() - 2), board) || alterColorPiece(Position(getX() - 1, getY() - 2), board)) possiblePositions.push_back(Position(getX() - 1, getY() - 2));
    }
    if(getX() < 7 && getY() > 1) {
        if(isFree(Position(getX() + 1, getY() - 2), board) || alterColorPiece(Position(getX() + 1, getY() - 2), board)) possiblePositions.push_back(Position(getX() + 1, getY() - 2));
    }
    if(getX() > 0 && getY() < 6) {
        if(isFree(Position(getX() - 1, getY() + 2), board) || alterColorPiece(Position(getX() - 1, getY() + 2), board)) possiblePositions.push_back(Position(getX() - 1, getY() + 2));
    }
    if(getX() < 7 && getY() < 6) {
        if(isFree(Position(getX() + 1, getY() + 2), board) || alterColorPiece(Position(getX() + 1, getY() + 2), board)) possiblePositions.push_back(Position(getX() + 1, getY() + 2));
    }
}

bool Knight :: isKnight() const {
    return true;
}