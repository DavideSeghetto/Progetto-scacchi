//SCRITTO DA BRUTTOMESSO ANDREA 

#include "../lib/boardSimplified.h"

#include <iostream>
#include <string>

void boardSimplified::move(std::string start, std::string end){
	int x1 = start[0] - 'A';
	int y1 = '8' - start[1];

	int x2 = end[0] - 'A';
	int y2 = '8' - end[1];
	
	board[y2][x2] = board[y1][x1];
	board[y1][x1] = ' ';
}

std::ostream& operator<<(std::ostream& os, boardSimplified b){
	for(int i=0; i<8; i++){
		os<<8-i<<" ";
		for(int j=0; j<8; j++){
			os<<b.board[i][j];
		}
		os<<std::endl;
	}
	os<<"  ABCDEFGH"<<std::endl;
	os<<std::endl;
	return os;
}

bool boardSimplified::checkPromotion(std::string pos){
	if((pos[1] == '8' || pos[1] == '1') && (tolower(pieceAt(pos)) == 'p')){
		return true;
	}
	return false;
}

char boardSimplified::pieceAt(std::string pos){
	int x = pos[0] - 'A';
	int y = '8' - pos[1];
	return board[y][x];
}


void boardSimplified::promotion(std::string pos, char p){
	int x = pos[0] - 'A';
	int y = '8' - pos[1];
	board[y][x] = p;
}

bool boardSimplified::checkCastling(std::string start, std::string end){
	if(tolower(pieceAt(end)) == 'r' && (start == "E1" || start == "E8")){
		int dX = abs(end[0] - start[0]); 	//prendo valore assoluto dello spostamento del re
		if(dX == 2){ 						//se re si muove di due caselle sicuramente fa arrocco
			return true;
		}
	}
	return false;
}

void boardSimplified::castling(std::string pos){ 
	std::string start = "xx", end = "xx";
	switch(pos[0]){						//in base alla colonna del re capisco se e' arrocco lungo o corto
		case 'G':
			start[0] = pos[0] + 1;
			end[0] = pos[0] - 1;
			start[1] = pos[1];
			end[1] = pos[1];
			move(start,end); 			//sposto torre da dx a sx del re
			break;
		case 'C':
			end[0] = pos[0] + 1;
			start[0] = pos[0] - 2; 		
			end[1] = pos[1];
			start[1] = pos[1];
			move(start,end); 			//sposto torre da sx a dx del re
			break;

	}
}