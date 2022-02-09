//Seghetto Davide 2008784

#include "../lib/bishop.h"

Bishop :: Bishop(int x, int y, bool color) {
    position.setX(x);
    position.setY(y);
    white = color;
    c = white ? 'a' : 'A';
    firstX = x;
}

void Bishop :: move(const Position& to, ChessBoard& board) {
    makePossiblePositions(board); //aggiorno il vettore di possibili posizioni
    
    if(!isValid(to)) throw new InvalidPosition(); //controllo se la mossa appartiene al vettore di possibili posizioni o meno
    else position = to; //aggiorno la variabile membro
}

void Bishop :: makePossiblePositions(ChessBoard& board) {
    possiblePositions.clear();

    for(int i = getX() + 1, j = getY() - 1; i < 8 && j > - 1; i++, j--) { //movimento in diagonale in alto a destra
        if(isFree(Position(i, j), board)) possiblePositions.push_back(Position(i, j)); //se la casella è libera, la pusho e proseguo col ciclo
        else if(alterColorPiece(Position(i, j), board)) { //se è occupata da un pezzo del colore opposto pusho la casella ed esco dal ciclo
            possiblePositions . push_back(Position(i, j));
            break;
        }
        else break; //se la casella è occupata da un pezzo dello stesso colore non pusho ed esco dal ciclo
    }

    for(int i = getX() - 1, j = getY() + 1; i > - 1 && j < 8; i--, j++) { //movimento in diagonale in basso a sinistra
        if(isFree(Position(i, j), board)) possiblePositions.push_back(Position(i, j));
        else if(alterColorPiece(Position(i, j), board)) {
            possiblePositions.push_back(Position(i, j));
            break;
        }
        else break;
    }

    for(int i = getX() + 1, j = getY() + 1; i < 8 && j < 8; i++, j++) { //movimento in diagonale in basso a destra
        if(isFree(Position(i, j), board)) possiblePositions . push_back(Position(i, j));
        else if(alterColorPiece(Position(i, j), board)) {
            possiblePositions . push_back(Position(i, j));
            break;
        }
        else break;
    }
    for(int i = getX() - 1, j = getY() - 1; i > - 1 && j > -1; i--, j--) { //movimento in diagonale in alto a sinistra
        if(isFree(Position(i, j), board)) possiblePositions.push_back(Position(i, j));
        else if(alterColorPiece(Position(i, j), board)) {
            possiblePositions.push_back(Position(i, j));
            break;
        }
        else break;
    }
}

int Bishop :: getFirstX() const {
    return firstX;
} 

bool Bishop :: isBishop() const{
    return true;
}