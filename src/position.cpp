//Seghetto Davide 2008784

#include "../lib/position.h"

Position :: Position() {
    x = - 1;
    y = - 1;
}

Position :: Position(int x, int y) {
    this -> x = x;
    this -> y = y;
}

int Position :: getX() const {
    return x;
}

int Position :: getY() const {
    return y;
}

void Position :: setX(int x) {
    this -> x = x;
}

void Position :: setY(int y) {
    this -> y = y;
}

Position& Position :: operator = (const Position& pos) {
    x = pos.x;
    y = pos.y;
    return *this;
}

bool Position :: operator == (const Position& pos) const {
    return (x == pos.x && y == pos.y);
}

Position& Position :: addPosition(const Position& v) {
    x += v.x;
    y += v.y;
    return *this;
}

std :: ostream& operator << (std :: ostream& os, const Position& p){
	char a, b;
    a = 'A' + p.getX();
    b = '8' - p.getY();
    os << a << b;
	return os;
}