//Seghetto Davide 2008784

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class ChessBoard;

class Pawn : public Piece {
 
    public:
    Pawn(int x, int y, bool color);
    void move(const Position& to, ChessBoard& board) override;
    void makePossiblePositions(ChessBoard& board) override; //aggiorna le possibili posizioni in cui il pedone può andare
    int getTurnMove() const; //restituisce il turno in cui il pedone si è spostato l'ultima volta
    void setTurnMove(int a) override; //imposta il turno in cui il pedone si è spostato
    bool getFirstMove() const override; //restituisce true se move viene chiamato per la prima volta (o deve ancora essere chiamato)
    void setFirstMove(bool fM);
    bool getEnPassant() const; //restituisce true se il pedone può subire l'en passant
    bool isPawn() const override; //restituisce true se chiamato su un pedone, false altrimenti

    private:
    bool firstMove = true;
    bool enPassant = false;
    int turnMove;
};

#endif
