//Seghetto Davide 2008784

#include "../lib/pawn.h"
#include "../lib/ChessBoard.h"

Pawn :: Pawn(int x, int y, bool color) {
    position.setX(x);
    position.setY(y);
    white = color;
    c = white ? 'p' : 'P'; //se è bianco il carattere è minuscolo, se nero viceversa
}

void Pawn :: move(const Position& to, ChessBoard& board) {
    makePossiblePositions(board); //prima di muovermi aggiorno le possibili posizioni in cui il pezzo può andare
    if(firstMove && isValid(to)) {
        int oldY = getY();
        position = to; //aggiorno la variabile membro
        firstMove = false; //dopo essersi mosso la prima volta rimane sempre false
        int newY = getY();
        if(abs(newY - oldY) == 2) enPassant = true; //se come prima mossa ha avanzato di due caselle può subire l'en passant
        else enPassant = false;
        return;
    }

    if(!isValid(to)) throw new InvalidPosition(); //nel caso in cui la posizione passata non appartenga al vettore di possibili posizioni
    
    if(abs(to.getX() - getX()) == 1 && board.at(to) != nullptr) { //caso in cui si mangia un pezzo in diagonale
        position = to;
        enPassant = false;
    }

    else if(abs(to.getX() - getX()) == 1 && board.at(to) == nullptr) { //in caso di en passant
        Position pos(to.getX(), getY()); //posizione del pezzo da mangiare con l'en passant
        Piece* toEliminate = board.at(pos);
        board.capture(toEliminate); //catturo il pezzo da mangiare
        board.setPiece(nullptr, pos); //imposta la cella della matrice su cui vi era il pezzo mangiato a nullptr
        position = to; 
    }
    
    else {
        enPassant = false; //poichè non era la prima mossa, sicuramente non può subire un en passant
        position = to;
    }
}

void Pawn :: makePossiblePositions(ChessBoard& board) {
    possiblePositions.clear();
    if(white) {
        if(firstMove && isFree(Position(getX(), getY() - 1), board) && isFree(Position(getX(), getY() - 2 ), board)) possiblePositions.push_back(Position(getX(), getY() - 2));
        if(isFree(Position(getX(), getY() - 1), board) && getY() > 0) possiblePositions.push_back(Position(getX(), getY() - 1));

        if(getX() < 7 && getY() > 0) { //movimento in diagonale in alto a destra
            Position to(getX() + 1, getY() - 1);
            //Controllo se posso mangiare in diagonale in alto a destra
            if(board.at(to) != nullptr && alterColorPiece(to, board)) possiblePositions.push_back(to);
            else {
                //Non posso, controllo se posso farlo usando l'en passant
                if(getY() == 3)  {
                    Position pos(to.getX(), getY()); //controllo nella casella pos con coordinata x la stessa di to e con coordinata y la stessa di this
                    if(board.at(pos) != nullptr && board.at(pos) -> isPawn()) {
                        //Ho controllato che pos sia diverso da nullptr e che vi sia un pedone. Controllo se i turni differiscono di 1
                        if(board.getTurn() - ((Pawn*)board.at(pos)) -> getTurnMove() == 1 && (((Pawn*)board.at(pos)) -> getEnPassant())) possiblePositions.push_back(to);
                    }
                }
            }
        }

        if(getX() > 0 && getY() > 0) { //movimento in diagonale in alto a sinistra
            Position to(getX() - 1, getY() - 1);
            if(board.at(to) != nullptr && alterColorPiece(to, board)) possiblePositions.push_back(to);
            else { //en passant
                if(getY() == 3) {
                    Position pos(to.getX(), getY());
                    if(board.at(pos) != nullptr && board.at(pos) -> isPawn()) {
                        if(board.getTurn() - ((Pawn*)board.at(pos)) -> getTurnMove() == 1 && (((Pawn*)board.at(pos)) -> getEnPassant())) possiblePositions.push_back(to);
                    }
                }    
            }
        }
    }

    if(!white) {
        if(firstMove && isFree(Position(getX(), getY() + 1), board) && isFree(Position(getX(), getY() + 2), board)) possiblePositions.push_back(Position(getX(), getY() + 2));
        if(isFree(Position(getX(), getY() + 1), board) && getY() < 7) possiblePositions.push_back(Position(getX(), getY() + 1));

        if(getX() < 7 && getY() < 7) {
            Position to(getX() + 1, getY() + 1); 
            if(board.at(to) != nullptr && alterColorPiece(to, board)) possiblePositions.push_back(to);
            else { //en passant
                if(getY() == 4) {
                    Position pos(to.getX(), getY());
                    if(board.at(pos) != nullptr && board.at(pos) -> isPawn()) {
                        if(board.getTurn() - ((Pawn*)board.at(pos)) -> getTurnMove() == 1 && (((Pawn*)board.at(pos)) -> getEnPassant())) possiblePositions.push_back(to);
                    }
                }
            }
        }
        
        if(getX() > 0 && getY() < 7) {
            Position to(getX() - 1, getY() + 1); 
            if(board.at(to) != nullptr && alterColorPiece(to, board)) possiblePositions.push_back(to);
            else { //en passant
                if(getY() == 4) {
                    Position pos(to.getX(), getY());
                    if(board.at(pos) != nullptr && board.at(pos) -> isPawn()) {
                        if(board.getTurn() - ((Pawn*)board.at(pos)) -> getTurnMove() == 1 && (((Pawn*)board.at(pos)) -> getEnPassant())) possiblePositions.push_back(to);
                    }
                }
            }
        }
    }
}

int Pawn :: getTurnMove() const {
    return turnMove;
}

void Pawn :: setTurnMove(int a) {
    turnMove = a;
}

bool Pawn :: getFirstMove() const {
    return firstMove;
}

void Pawn :: setFirstMove(bool fM) {
    firstMove = fM;
}

bool Pawn :: getEnPassant() const {
    return enPassant;
}

bool Pawn :: isPawn() const {
    return true;
}