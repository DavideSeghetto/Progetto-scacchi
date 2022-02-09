//Seghetto Davide 2008784

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

    public:
    Knight(int x, int y, bool color);
    void move(const Position& to, ChessBoard& board) override;
    void makePossiblePositions(ChessBoard& board) override; //aggiorna il vettore di possibili posizioni
    bool isKnight() const override; //restituisce true solo se chiamato su un oggetto di tipo Knight
};

#endif
