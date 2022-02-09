//Seghetto Davide 2008784

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

    public:
    Queen(int x, int y, bool color);
    void move(const Position& to, ChessBoard& board) override;
    void makePossiblePositions(ChessBoard& board) override; //aggiorna il vettore di possibili posizioni
};

#endif
