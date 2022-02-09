//Seghetto Davide 2008784

#include "../lib/rook.h"
#include "../lib/ChessBoard.h"

Rook :: Rook(int x, int y, bool color) {
    position.setX(x);
    position.setY(y);
    white = color;
    c = white ? 't' : 'T';
}

void Rook::move(const Position& to, ChessBoard& board) {
    makePossiblePositions(board); //aggiorno le possibili posizioni
  
    if(firstMove) {
        if(!isValid(to)) throw new InvalidPosition(); //controllo se la mossa appartiene al vettore di possibili posizioni o meno
        else {
            position = to; //aggiorno la variabile membro
            firstMove = false;
            return;
        }
    }
  
    if(!isValid(to)) throw new InvalidPosition();
    else position = to; 
}

void Rook :: makePossiblePositions(ChessBoard& board) {
    possiblePositions.clear();

    for(int i = getY() + 1; i < 8; i++) {
        if(isFree(Position(getX(), i), board)) possiblePositions.push_back(Position(getX(), i)); //se la posizione è libera la pusho nel vettore di possibili posizioni e continuo il ciclo
        else if(alterColorPiece(Position(getX(), i), board)) { //se è occupata da un pezzo avversario pusho la posizione e termino il ciclo (oltre non posso andare)
            possiblePositions.push_back(Position(getX(), i));
            break;
        }
        else break; //se è occupata da un pezzo dello stesso colore esco dal ciclo senza pusharla
    }

    for(int i = getY() - 1; i > - 1; i--) {
        if(isFree(Position(getX(), i), board)) possiblePositions.push_back(Position(getX(), i));
        else if(alterColorPiece(Position(getX(), i), board)) {
            possiblePositions.push_back(Position(getX(), i));
            break;
        }
        else break;
    }

    for(int i = getX() + 1; i < 8; i++) {
        if(isFree(Position(i, getY()), board)) possiblePositions.push_back(Position(i, getY()));
        else if(alterColorPiece(Position(i, getY()), board)) {
            possiblePositions.push_back(Position(i, getY()));
            break;
        }
        else break;
    }

    for(int i = getX() - 1; i > - 1; i--) {
        if(isFree(Position(i, getY()), board)) possiblePositions.push_back(Position(i, getY()));
        else if(alterColorPiece(Position(i, getY()), board)) {
            possiblePositions.push_back(Position(i, getY()));
            break;
        }
        else break;
    }
}

bool Rook :: isRook() const {
    return true;
}

bool Rook :: getFirstMove() const {
    return firstMove;
}