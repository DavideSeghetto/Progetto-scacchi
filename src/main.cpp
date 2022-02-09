//SCRITTO DA BRUTTOMESSO ANDREA 

#include "../lib/ChessBoard.h"
#include "../lib/piece.h"
#include "../lib/king.h"
#include "../lib/queen.h"
#include "../lib/rook.h"
#include "../lib/knight.h"
#include "../lib/bishop.h"
#include "../lib/pawn.h"
#include "../lib/InvalidPiece.h"

#include <fstream>
#include <time.h>    
#include <stdlib.h>   

using namespace std;

//IN TUTTO IL CODICE SI CONSIDERA, PER CONVENZIONE, IL VALORE TRUE DI UN BOOLEANO ASSOCIATO
//AI PEZZI DI COLORE BIANCO ED IL VALORE FALSE ASSOCIATO AI PEZZI DI COLORE NERO 

//Funzione che genera una scacchiera e gestisce le interazioni di gioco tra un giocatore reale
//ed il pc, quest'ultimo effettua mosse casuali con l'unico obiettivo di non lasciare che il re
//venga mangiato o lasciato sotto scacco
void player_vs_computer();

//Funzione per gestire una partita effettuata tra due pc. Il comportamento del pc e' quello
//illustrato nella funzione player_vs_computer()
void computer_vs_computer();

//Funzione che accetta due stringhe, le coordinate sulla scacchiera di partenza e arrivo del movimento
//e le converte in due esemplari di Position che contengono le coordinate del movimento nella matrice
//associata al pezzo. Ritora un vettore di due posizioni nell'ordine: {posizione di partenza, posizione d'arrivo}
//Lancia InvalidPosition se e solo se le coordinate fornite escono dai limiti della scacchiera.
Position* converter(string start, string end);

//Funzione adibita alla promozione di un pedone. Accetta una scacchiera su cui eseguire l'azione, il char
//corrispondente al pezzo da ottenere, il pezzo da promuovere e il colore del pezzo. Viene invocata se e solo se
//le precondizioni della promozione sono rispettate, cioè se il pezzo di trova in un estremo della scacchiera ed e'
//un pedone.
//Lancia InvalidPiece se e solo se il char fornito non corrisponde ad un pezzo valido per la promozione.
void promotion(ChessBoard& cb, char p, Piece* pawn, bool color);

//Funzione per controllare che il pezzo di cui si vuole eseguire l'azione sia posseduto dal giocatore corrente
//Si forniscono una scacchiera, la posizione del pezzo e il colore del giocatore corrente, ritorna TRUE se e solo se
//il colore del pezzo sulla scacchiera corrisponde al colore del giocatore corrente.
void check_color(ChessBoard& cb, Position p, bool player_color);

int main(int argc, char **argv){

    
    if(argc > 1){
        string tmp = argv[1];
        if(tmp == "cc") computer_vs_computer();
        else if(tmp == "pc") player_vs_computer();
        else cout<<"ERROR. Invalid command, terminating programm."<<endl;
    }else{
        cout<<"Not enough arguments. Terminating programm. "<<endl;
    }
    
    return 0;
}

void player_vs_computer(){
    srand(time(NULL));

    ChessBoard cb;
    cb.NewGame();  
    cout<<cb;

    ofstream os{"../texts/log_pc.txt"};

    //Genera casualmente colore del player
    bool player_is_white = false;
    int rnd = rand() % 2 + 1;
    if(rnd == 1) player_is_white = true;
    cout<<"Player color: ";
    if(player_is_white) cout<<"white."<<endl;
    else cout<<"black."<<endl;
    
    //Creo puntatori ai re, verranno passati ad isTie() e inCheckMate()
    Piece *bK = cb.getKing(false), *wK = cb.getKing(true);
    Piece* curr = wK; 
    
    //Stabilisco se comincia player o pc
    bool player_turn = player_is_white;
    
    bool tie = false, checkmate = false;
    while(!tie && !checkmate){
        //Gestione interazione con il player
        bool valid_move;
        int counter = 0;
        if(player_turn){ 
            Position* pos;
            valid_move = false;
            string start, end;

            while(!valid_move){
                //Gestisco la richiesta di stampare la scacchiera
                do{
                    cout<<"Digitare mossa nel formato \"X0 X0\": ";
                    cin>>start>>end;
                    
                    start[0] = toupper(start[0]);
                    end[0] = toupper(end[0]);

                    if(start[1] == 'x' && end[1] == 'x'){
                        start[1] = toupper(start[1]);
                        end[1] = toupper(end[1]);
                    }
                    if(start == "XX" && end == "XX") cout<<cb;
                } while(start == "XX" && end == "XX");
                
                try{
                    pos = converter(start,end);
                    check_color(cb, pos[0], player_is_white);
                    //Simulo la mossa per vedere se il re finisce sotto scacco a causa dello spostamento
                    ChessBoard tryChessBoard( cb );
        			tryChessBoard.tryMove(pos[0], pos[1]);
        			Piece* tryKing = tryChessBoard.getKing(player_turn);
        			std::vector<Piece*> listOfThreats;
        			tryChessBoard.piecesThatThreaten(tryKing, listOfThreats);
        			if (listOfThreats.size() > 0){
        				cout<<"Invalid move, King can be eaten"<<endl;
                        continue; //Faccio ripartire il ciclo dall'inizio nel caso il re venga scoperto
					}else{
                        cb.move(pos[0], pos[1]);
                        os<<start<<" "<<end<<" ";
                        //Controllo se sono in una situazione valida per la promozione
                        if(end[1] == '1' || end[1] == '8' ){
                            if(cb.at(pos[1])->isPawn()){
                                cout<<"Type selected piece:"<<endl;
                                bool valid_piece = false;
                                while(!valid_piece){
                                    cout<<"--> ";
                                    char p;
                                    cin>>p;

                                    if(player_is_white) p = tolower(p);
                                    else p = toupper(p);

                                    try{
                                        promotion(cb, p, cb.at(pos[1]), player_is_white);
                                        os<<p;
                                        valid_piece = true;
                                    }catch(InvalidPiece* e){
                                        cout<<"Invalid piece."<<endl;
                                    }
                                }
                            }
                        }
                    }
                    os<<endl;
                    valid_move = true;
                }catch(InvalidPosition* e){
                    cout<<"An invalid position was entered. Retry: "<<endl;
                }
            }
        }else{ //Gestione mosse casuali del pc
            valid_move = false;
            
            //Genero una lista dei pezzi che potrei muovere
            vector<Piece*> pieces;
            if(player_is_white) pieces = cb.getListOfBlackPieces(); 
            else pieces = cb.getListOfWhitePieces();
            int counter = 0;
            while(!valid_move){
                Position start, end;
                if(cb.isCheck(curr)){ //Se il re è sotto scacco devo eseguire delle mosse precise per salvarlo
                    vector<Position> priorityMoves = cb.getPriorityMoves();
                    rnd = rand() % (priorityMoves.size()/2);
                    start = priorityMoves[rnd*2];
                    end   = priorityMoves[(rnd*2)+1];
                    cb.clearPriorityMoves();
                }else{ //Altrimenti le scelgo totalmente a caso
                    vector<Position> moves;
                    while(moves.size() == 0){ //Cerco un pezzo che abbia mosse disponibili 
                        rnd = rand() % pieces.size();
                        pieces[rnd]->makePossiblePositions(cb);
                        moves = pieces[rnd]->getPossiblePositions();
                    }
                    moves = pieces[rnd]->getPossiblePositions();
                    int rnd2 = rand() % moves.size();
                    start = pieces[rnd]->getPosition();
                    end = moves[rnd2]; 
                }

                try{ //Simulo la mossa per vedere se va a scoprire il re
                    ChessBoard tryChessBoard(cb);
                    tryChessBoard.tryMove(start, end);
                    Piece* tryKing = tryChessBoard.getKing(!player_is_white);
                    std::vector<Piece*> listOfThreats;
                    tryChessBoard.piecesThatThreaten(tryKing, listOfThreats);
                    if (listOfThreats.size() > 0) {
                        counter++;
                        continue;
                    } else {
                        cb.move(start, end);
                        valid_move = true;
                        os<<start<<" "<<end<<" ";
                        //Controllo se siamo in una situazione di promozione
                        if(end.getY() == 0 || end.getY() == 7){
                            if(cb.at(end)->isPawn()){
                                char obtainablePieces[] = {'d','t','c','a'};
                                rnd = rand() % 4;
                                char p = obtainablePieces[rnd];

                                if(player_is_white) p = tolower(p);
                                else p = toupper(p);
                                try{
                                    promotion(cb, p, cb.at(end), player_is_white);
                                    os<<p;
                                }catch(InvalidPiece* e){
                                    cout<<"Pezzo non valido."<<endl;
                                }
                            }
                        }
                        os<<endl;
                        cout<<"Computer has moved."<<endl;
                    }
                } catch (InvalidPosition* e){
                    
                }
            }

        }
        player_turn = !player_turn;
        if(curr == wK) curr = bK;
        else curr = wK;

        tie = cb.isTie(curr);
        checkmate = cb.isCheckMate(curr);
    }

    //Serve solo per stampare messaggio di servizio
    if(checkmate){
        cout << "Checkmate!" << endl;
    }else if(tie){
        cout << "Tie!" << endl;
    }

    cout<<"Game over."<<endl;
    os.close();
}

void computer_vs_computer() {
    srand(time(NULL));

    ChessBoard cb;
    cb.NewGame();
        
    ofstream os{"../texts/log_cc.txt"};

    bool turn = true; //per convenzione in tutto il codice true = bianco
    constexpr int max_moves = 250;
    int cont_moves = 0;
    bool valid_move;

    bool tie = false, checkmate = false;
    while(!tie && !checkmate && cont_moves < max_moves ) {
        //Il comportamento e' analogo alla scelta della mossa casuale del pc nella funzione player_vs_computer()
        valid_move = false;
        vector<Piece*> pieces = turn ? cb.getListOfWhitePieces() : cb.getListOfBlackPieces();
        
        int rnd;

        int counter = 0;
        while(!valid_move){
            if(counter > 100){
                cout<<"Stalemate"<<endl;
                tie = true;
                break;
            }

            Piece* pieceToMovePtr = nullptr;
            Position start, end;
            vector<Position> moves;
            if(cb.isCheck(cb.getKing(turn))){
                vector<Position> priorityMoves = cb.getPriorityMoves();
                rnd = rand() % (priorityMoves.size()/2);
                start = priorityMoves[rnd*2];
                end = priorityMoves[(rnd*2)+1];
                cb.clearPriorityMoves();
                pieceToMovePtr = cb.at(start);
            }else{
                while(moves.size() == 0){ 
                    rnd = rand() % pieces.size();
                    pieces[rnd]->makePossiblePositions(cb);
                    moves = pieces[rnd]->getPossiblePositions();
                }

                pieceToMovePtr = pieces[rnd];
                moves = pieces[rnd]->getPossiblePositions();
                int rnd2 = rand() % moves.size();
                start = pieces[rnd]->getPosition();
                end = moves[rnd2];
            }

            try{
                ChessBoard tryChessBoard(cb);
                tryChessBoard.tryMove(start, end);
                Piece* tryKing = tryChessBoard.getKing(turn);
                std::vector<Piece*> listOfThreats;
                tryChessBoard.piecesThatThreaten(tryKing, listOfThreats);

                if(listOfThreats.size() > 0){
                    counter++;
                    continue;
                }else{
                    cb.move(start, end);
                    valid_move = true;
                    os<<start<<" "<<end;
                    if(end.getY() == 0 || end.getY() == 7){
                        if(cb.at(end)->isPawn()){
                            char obtainablePieces[] = {'d','t','c','a'};
                            rnd = rand() % 4;
                            char p = obtainablePieces[rnd];

                            if(turn == true) p = tolower(p);
                            else p = toupper(p);
                                
                            try{
                                promotion(cb, p, cb.at(end), turn);
                                os<<" " << p;
                            }catch(InvalidPiece* e){
                                cout<<"Invalid piece. Retry."<<endl;
                            }
                        }
                    }
                    os<<endl;
                }
            }catch(InvalidPosition* e){
                cout<<"Wrong coordinates. Retry."<<endl;
            }
        }
        
        cont_moves++;
        Piece* myKing = cb.getKing(turn);            
        Piece* otherKing = cb.getKing(!turn);

        checkmate = cb.isCheckMate(otherKing);
        if(checkmate){
            cout<<"Checkmate!"<<endl;
            break;
        }

        tie = cb.isTie(otherKing);
        if(tie){
            cout <<"Tie"<< endl;
            break;
        }

        turn = !turn;
    }

    if(cont_moves >= max_moves){
        cout<<"Moves limit."<<endl;
    }
    cout<<"Game over."<<endl;
}

Position* converter(string start, string end){
    if(start[0] < 'A' || start[0] > 'H' || start[1] < '0' || start[1] > '8' || end[0] < 'A' || end[0] > 'H' || end[1] < '0' || end[1] > '8')
        throw new InvalidPosition();
    
    Position* p = new Position[2];
    
    int x = start[0] - 'A';
    int y = '8' - start[1];
    p[0] = Position(x,y);

    x = end[0] - 'A';
    y = '8' - end[1];
    p[1] = Position(x,y);

    return p;
}

void promotion(ChessBoard& cb, char p, Piece* pawn, bool color){
    Piece* promoted;
    switch(p){
        case 'd':
        case 'D':
            promoted = new Queen  (0, 0, color);
            break;
        case 't':
        case 'T':
            promoted = new Rook  (0, 0, color);
            break;
        case 'c':
        case 'C':
            promoted = new Knight  (0, 0, color);
            break;
        case 'a':
        case 'A':
            promoted = new Bishop  (0, 0, color);
            break;
        default:
            throw new InvalidPiece();
    }
    cb.promotion(pawn, promoted);
}

void check_color(ChessBoard& cb, Position p, bool player_color){
    if(cb.getPieceColor(p) != player_color) throw new InvalidPosition();
}
