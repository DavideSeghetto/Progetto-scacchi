//SCRITTO DA BRUTTOMESSO ANDREA 

#include <iostream>
#include <fstream>
#include <string>
// librerie per lo sleep
#include <chrono>
#include <thread>

#include "../lib/boardSimplified.h"

using namespace std;

void file_replay(string i, string o);
void video_replay(string i);

int main(int argc, char **argv){	
	try{
		string command = argv[1];
		if(command == "f"){
			file_replay(argv[2], argv[3]);
		}else if(command == "v"){		
			video_replay(argv[2]);
		}else{
			cout<<"ERROR: no command found. Program quit."<<endl;
		}
	} catch (logic_error){
		cout<<"ERROR: not enough arguments. Program quit."<<endl;
	}	

	return 0;
}

void video_replay(string i){
	ifstream is{i};

	//setup dello sleep ad 1 secondo
	chrono::seconds time(1);

	boardSimplified board;

	string s,e;
	while(is>>s>>e){
		cout<<s<<" "<<e<<endl;
		board.move(s,e);
		if(board.checkPromotion(e)){
			char p;
			is>>p;
			board.promotion(e,p);
		} else if(board.checkCastling(s,e)){
			board.castling(e);
		}
		cout<<board;
		this_thread::sleep_for(time);
	}

}

void file_replay(string i, string o){
	ifstream is{i}; //apro stream di input da i
	ofstream os{o}; //apro streamo di output in o

	boardSimplified board;
	string s,e;
	while(is>>s>>e){
		board.move(s,e);
		if(board.checkPromotion(e)){
			char p;
			is>>p;
			board.promotion(e,p);
		} else if(board.checkCastling(s,e)){
			board.castling(e);
		}
		os<<board;
	}
}