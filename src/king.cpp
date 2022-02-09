//Seghetto Davide 2008784

#include "../lib/king.h"
#include "../lib/ChessBoard.h"

King :: King(int x, int y, bool color) {
    position.setX(x);
    position.setY(y);
    white = color;
    c = white ? 'r' : 'R';
}

void King :: move(const Position& to, ChessBoard& board) {
    makePossiblePositions(board); //aggiorno le possibili posizioni in cui può andare
    if(firstMove) {
        if(isValid(to)) { //controllo se la mossa appartiene al vettore di possibili posizioni o meno
            int oldX = getX();
            position = to; //aggiorno la posizione
            firstMove = false; //dopo essersi mosso la prima volta rimane sempre false
            int newX = getX();
            //controllo se si è spostato di due caselle in orizzontale; se così vuol dire che devo fare l'arrocco, quindi chiamo anche il move di Rook
            if(oldX - newX == 2) board.move(Position(oldX - 4, getY()), Position(oldX - 1, getY())); //arrocco lungo
            if(oldX - newX == - 2) board.move(Position(oldX + 3, getY()), Position(oldX + 1, getY())); //arrocco corto
            return;
        }
        else throw new InvalidPosition();
    }
    if(!isValid(to)) throw new InvalidPosition();
    else position = to;
}

void King :: makePossiblePositions(ChessBoard& board) {
    possiblePositions.clear();
    if(firstMove) { //se è la prima mossa posso fare l'arrocco, controllo:
        Position pos3(getX() + 3, getY()); //arrocco corto
        //tre caselle a destra del re deve esserci una torre che non si è ancora mossa (firstMove deve essere true)
        if(board.at(pos3) != nullptr && board.at(pos3) -> isRook() && board.at(pos3) -> getFirstMove()) {
            Position pos1(getX() + 1, getY());
            Position pos2(getX() + 2, getY());
            //controllo se nel tragitto non ci sono pezzi che bloccano l'arrocco
            if(isFree(pos1, board) && isFree(pos2, board)) {
                //controllo che nel tragitto il re non finisca sotto scacco
                if(!board.canBeEaten(white, pos1) && !board.canBeEaten(white, pos2)) possiblePositions.push_back(pos2);
            }
        }

        Position pos7(getX() - 4, getY()); //arrocco lungo
        //quattro caselle a sinistra del re deve esserci una torre che non si è ancora mossa (firstMove deve essere true)
        if(board.at(pos7) != nullptr && board.at(pos7) -> isRook() && board.at(pos7) -> getFirstMove()) {
            Position pos4(getX() - 1, getY());
            Position pos5(getX() - 2, getY());
            Position pos6(getX() - 3, getY());
            //controllo se nel tragitto non ci sono pezzi che bloccano l'arrocco
            if(isFree(pos4, board) && isFree(pos5, board) && isFree(pos6, board)) {
                //controllo che nel tragitto il re non finisca sotto scacco
                if(!board.canBeEaten(white, pos4) && !board.canBeEaten(white, pos5)) possiblePositions.push_back(pos5);
            }
        }
    }
    //le otto possibili caselle in cui può andare il re, controllo se non escono dalla scacchiera e se non vi sono pezzi dello stesso colore
    if(getY() > 0) {
        Position pos(getX(), getY() - 1);
        if(isFree(pos, board) || alterColorPiece(pos, board)){
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }
    if(getY() < 7) {
        Position pos(getX(), getY() + 1);
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }
    if(getX() < 7) {
        Position pos(getX() + 1, getY());
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)){
                possiblePositions.push_back(pos);
            }
        }
    }
    if(getX() > 0) {
        Position pos(getX() - 1, getY());
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }
    if(getX() < 7 && getY() < 7) {
        Position pos(getX() + 1, getY() + 1);
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }
    if(getX() > 0 && getY() > 0) {
        Position pos(getX() - 1, getY() - 1);
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }
    
    if(getX() < 7 && getY() > 0) {
        Position pos(getX() + 1, getY() - 1);
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }

    if(getX() > 0 && getY() < 7) {
        Position pos(getX() - 1, getY() + 1);
        if(isFree(pos, board) || alterColorPiece(pos, board)) {
            if(!board.canBeEaten(white, pos)) possiblePositions.push_back(pos);
        }
    }
}

bool King :: getFirstMove() const {
    return firstMove;
}

void King :: setFirstMove(bool fM) {
    firstMove = fM;
}

bool King :: isKing() const {
    return true;
}