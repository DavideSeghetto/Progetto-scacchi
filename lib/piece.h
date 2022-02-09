//Seghetto Davide 2008784

#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include "InvalidPosition.h"
#include <vector>

class ChessBoard;

class Piece { //da essa derivano tutti i vari pezzi
    protected:
    Position position;
    char c;
    bool white; //per convenzione, un pezzo è bianco (true) oppure nero (false)
    std :: vector<Position> possiblePositions; //vettore di possibili posizioni in cui un pezzo può spostarsi

    public:
    Position getPosition() const;
    int getX() const; 
    int getY() const; 
    char print() const;
    bool color() const;
    virtual bool getFirstMove() const;
    void setPosition(Position& pos);
    bool isFree(const Position& to, ChessBoard& board) const; //restituisce true se su to non vi è nessun pezzo, false altrimenti
    bool alterColorPiece(const Position& to, ChessBoard& board) const; //restituisce true se su to vi è un pezzo del colore opposto a quello del pezzo su cui la funzione viene chiamata, false altrimenti
    virtual bool isValid(const Position& to) const; //controlla se to appartiene al vettore possiblePositions
    std :: vector<Position> getPossiblePositions();
    virtual void makePossiblePositions(ChessBoard& board) = 0; //aggiorna il vettore di possibili posizioni
    virtual void move(const Position& to, ChessBoard& board) = 0;
    virtual void setTurnMove(int a); //imposta il turno in cui il pezzo si sposta, utilizzata per pedone
    //is...() restituiscono true se il pezzo è ...
    virtual bool isKing() const;
    virtual bool isRook() const;
    virtual bool isKnight() const;
    virtual bool isBishop() const;
    virtual bool isPawn() const;
    bool operator == (Piece& piece) const;
    bool operator != (Piece& piece) const;
    virtual ~Piece();
};

#endif
