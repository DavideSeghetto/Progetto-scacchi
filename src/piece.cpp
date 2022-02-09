//Seghetto Davide 2008784

#include "../lib/piece.h"
#include "../lib/ChessBoard.h"

Position Piece :: getPosition() const {
    return position;
}

int Piece :: getX() const {
    return position.getX();
}

int Piece :: getY() const {
    return position.getY();
}

bool Piece :: color() const {
    return white;
}

char Piece :: print() const {
    return c;
}

bool Piece :: getFirstMove() const {
    return false;
}

void Piece :: setPosition(Position& pos) {
    position = pos;
}

bool Piece :: isFree(const Position& to, ChessBoard& board) const {
    return board.at(to) == nullptr;
}

bool Piece :: alterColorPiece(const Position& to, ChessBoard& board) const {
  if (board.at(to) != nullptr) return board.getPieceColor(to) != white;
  return false;
}

bool Piece :: isValid(const Position& to) const {
    for(int i =  0; i < possiblePositions.size(); i++) if(possiblePositions.at(i) == to) return true;
    return false;
}

std :: vector<Position> Piece::getPossiblePositions(){
    return possiblePositions;
}

void Piece :: setTurnMove(int a) {
    return;
}

bool Piece :: isKing() const {
    return false;
}

bool Piece :: isRook() const {
    return false;
}

bool Piece :: isBishop() const {
    return false;
}

bool Piece :: isKnight() const {
    return false;
}

bool Piece :: isPawn() const {
    return false;
}

bool Piece :: operator == (Piece& piece) const {
    return c == piece.print();
}

bool Piece :: operator!= (Piece& piece) const {
    return (c != piece.print());
}

Piece :: ~Piece() {

}