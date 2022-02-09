//Seghetto Davide 2008784

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

    public: 
    Rook(int x, int y, bool color);
    void move(const Position& to, ChessBoard& board) override;
    void makePossiblePositions(ChessBoard& board) override; //aggiorna il vettore di possibili posizioni
    bool getFirstMove() const override; //restituisce true se chiamata prima di aver chiamato per la prima volta move
    bool isRook() const override; //restituisce true solo se chiamata su un oggetto di tipo Rook

    private:
    bool firstMove = true;
};

#endif
