//gaia casotto

/* la parte piu' antipatica e' stata la funzione di "look ahead", ovvero determinare se la mossa che si stava facendo metteva il re di chi
 stava muovendo sotto scacco da parte dell'avversario. Per evitare queste mosse "suicide" ho implementato delle scacchiere "look ahead" di un livello piu' basso su cui viene provata la mossa e viene determinato se la mossa e' valida o no.*/

/*  8    T                 // known bugs: facendo repeat 10000 ./scacchi cc ho trovato questa configurazione
    7     C                // della scacchiera che ha fatto andare in loop il programma. Non si rende conto che e' stalemate.
    6   A   R              // non sono riuscita a debuggarlo e trovare l'errore :/ 
    5      P
    4  Pr
    3 A   A
    2       P
    1  T

      ABCDEFGH  */



#ifndef ChessBoard_h
#define ChessBoard_h

#include <iostream>
#include <string>
#include <vector>

#include "position.h"

class Piece;
class Pawn;

class ChessBoard{
private:
    Piece* m_board[8][8];
    std::vector<Piece*> m_listOfBlackPieces;
    std::vector<Piece*> m_listOfWhitePieces;
    std::vector<ChessBoard*> m_listOfSnapshots;   //lista delle disposizioni passate della scacchiera (per la patta).
    std::vector<Position> m_listOfPriorityMoves;  //lista delle mosse da effettuare se il computer e' sotto scacco.
    int m_movesWithoutCaptures;
    int m_pawnsHaveNotMoved;
    int m_numOfTurns;
    int m_numOfPieces;
    bool m_allowRecursion;                      //variabile che permette o no la ricorsione all'interno delle schacchiere di "look ahead".
    
    
    static constexpr bool BLACK_PIECE = false;
    static constexpr bool WHITE_PIECE = true;

public:
    ChessBoard();                     //costruttore del chessboard
    ChessBoard(const ChessBoard& cb); //costruttore di copia.
    ~ChessBoard();                    //distruttore.
    void NewGame();                   //inizializza il gioco.
    std::string printBoard() const;
    Piece* at(Position pos) const;
    Piece* getKing(bool color);
    void   setPiece(Piece* p, Position pos);
    std::vector<Piece*>&   getListOfBlackPieces() { return m_listOfBlackPieces; }
    std::vector<Piece*>&   getListOfWhitePieces() { return m_listOfWhitePieces; }
    std::vector<Position>& getPriorityMoves() { return m_listOfPriorityMoves; }
    void clearPriorityMoves() { m_listOfPriorityMoves.clear(); }
    void clearSnapshotList();
    bool getPieceColor(Position pos);
    void move(Position from, Position to);
    void tryMove(Position from , Position to);   //funzione necessaria per il "look ahead"; opera su una scacchiera copiata, e
                                                 //determina in base all'outcome se la mossa effettuata e' valida anche sulla scacchiera
                                                 //su cui si sta giocando.
    bool isOccupied(const Position to); //passo le coordinate della casella e controlla se questa è occupata
    void capture(Piece* toEliminate);   //cattura di un pezzo.
    ChessBoard* snapshot();             //fa una "foto" allo stato della scacchiera (serve per la patta).
    int getTurn() const { return m_numOfTurns; }
    bool operator==(const ChessBoard& cb) const;
    friend std::ostream& operator<<(std::ostream& os, const ChessBoard& cb);

    
    
    //MOSSE SPECIALI
    std::vector<Piece*>& piecesThatThreaten(Piece* king, std::vector<Piece*>& listOfThreats);  //restituisce la lista dei pezzi che minacciano king.
    bool enemyKingIsClose(Position pos, bool color);
    std::vector<Piece*>& remainingPieces(std::vector<Piece*>& listOfRemainingPieces);  //restituisce tutti i pezzi rimanenti oltre ai re.
    bool canBeEaten(bool color, const Position& pos);
    bool canBeCovered(Piece* king, std::vector<Piece*>& listOfThreats); //metodi per determinare se e' scacco/ o scacco matto
    bool canEatThreat(Piece* king, std::vector<Piece*>& listOfThreats); // aiutano anche il computer a difendere il proprio re
    bool canEscape(Piece* king);                                        //nel caso in cui si riesca a uscire dalla condizione di
    bool isCheck(Piece* king);                                          //scacco.
    bool isCheckMate(Piece* king);
    bool isStalemate(Piece* king);   // stallo
    bool fiftyMoveRule();            // e altri metodi
    bool thirdRepetition();          // per determinare se
    bool isDeadPosition();           // si tratta di patta.
    bool isTie(Piece* king); //patta.
    void promotion(Piece* pawn, Piece* choiceOfPromotion);   //promozione.
};


#endif

