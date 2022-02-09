//Seghetto Davide 2008784

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

    public:
    Bishop(int x, int y, bool color);
    void move(const Position& to, ChessBoard& board) override;
    void makePossiblePositions(ChessBoard& board) override;
    int getFirstX() const; //restituisce la coordinata x della posizione in cui si trova l'alfiere ad inizio partita
    bool isBishop() const override;

    private:
    int firstX;
};

#endif
