//Seghetto Davide 2008784

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
 
    public:
    King(int x, int y, bool color);
    void move(const Position& to, ChessBoard& board) override; //l'arrocco si esegue indicando la casella di partenza e di arrivo del re 
    void makePossiblePositions(ChessBoard& board) override;
    virtual bool getFirstMove() const override; //restituisce true se viene chiamata prima di muovere il re
    void setFirstMove(bool fM); 
    bool isKing() const override; //restituisce true solo se chiamata su un oggetto king
    
    private:
    bool firstMove = true;
};

#endif
