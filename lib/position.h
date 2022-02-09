//Seghetto Davide 2008784

#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
    private:
    int x;
    int y;

    public:
    Position();
    Position(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    Position& operator = (const Position& pos); //assegnamento di copia
    bool operator == (const Position& pos) const;
    Position& addPosition(const Position& v); //controlla se le poszioni tra il re e il pezzo che minaccia lo scacco possono venire coperte da qualcuno
    friend std::ostream& operator<<(std::ostream& os, const Position& p); //funzione per stampare le posizioni nel log della partita
};

#endif
