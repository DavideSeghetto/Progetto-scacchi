//gaia casotto


#include <cmath>
#include <string>

#include "../lib/ChessBoard.h"
#include "../lib/piece.h"
#include "../lib/rook.h"
#include "../lib/queen.h"
#include "../lib/king.h"
#include "../lib/bishop.h"
#include "../lib/knight.h"
#include "../lib/pawn.h"

 ChessBoard::ChessBoard(){
     for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                m_board[i][j] = nullptr;
        }
    }
     m_movesWithoutCaptures = 0;
     m_pawnsHaveNotMoved    = 0;
     m_numOfTurns           = 1;
     m_numOfPieces          = 0;
     m_allowRecursion = true; 
 }

ChessBoard::ChessBoard(const ChessBoard& cb) {
    m_movesWithoutCaptures = cb.m_movesWithoutCaptures;
    m_pawnsHaveNotMoved    = cb.m_pawnsHaveNotMoved;
    m_numOfTurns           = cb.m_numOfTurns;
    m_allowRecursion = false;   //vieta di andare in ricorsione infinita.
    for(int i = 0; i < 8; i++){
        for(int j =0; j < 8; j++){
            if(cb.m_board[i][j] == nullptr){
                m_board[i][j] = nullptr;
            } else {
                Piece* piecePTR = cb.m_board[i][j];
                bool color = piecePTR->color();
                char typeOfPiece = piecePTR->print();
                Piece* newPiecePTR = nullptr;
                switch(tolower(typeOfPiece)){
                    case 't' : newPiecePTR = new Rook  (j, i, color); break;
                    case 'c' : newPiecePTR = new Knight(j, i, color); break;
                    case 'a' : newPiecePTR = new Bishop(j, i, color); break;
                    case 'd' : newPiecePTR = new Queen (j, i, color); break;
                    case 'r' :
                    {
                        King* kingPTR = new King  (j, i, color);   //basically un copy constructor di piece.
                        kingPTR->setFirstMove(piecePTR->getFirstMove());
                        newPiecePTR = kingPTR;
                    }
                        break;
                    case 'p' :
                    {
                        Pawn* pawnPTR = new Pawn  (j, i, color);
                        pawnPTR->setFirstMove( (piecePTR)->getFirstMove() );
                        newPiecePTR = pawnPTR;
                    }
                        break;
                    default:
                        std::cout << "!!!!!ERROR!!!!!" << std::endl;  //se succede vuol dire che in chessboard ci sono pezzi garbage.
                }
                m_board[i][j] = newPiecePTR;
                if(color){
                    m_listOfWhitePieces.push_back(newPiecePTR);
                } else {
                    m_listOfBlackPieces.push_back(newPiecePTR);
                }
            }
        }
    }
}

ChessBoard::~ChessBoard(){
    for(int i = 0; i < m_listOfWhitePieces.size(); i++){
        delete m_listOfWhitePieces.at(i);
    }
    for(int j = 0; j < m_listOfBlackPieces.size(); j++){
        delete m_listOfBlackPieces.at(j);
    }
    for(int k = 0; k < m_listOfSnapshots.size(); k++){
        delete m_listOfSnapshots.at(k);
    }
}

 void ChessBoard::NewGame(){
     m_numOfPieces = 32;
     m_board[0][0] = new Rook  (0, 0, BLACK_PIECE);
     m_board[0][1] = new Knight(1, 0, BLACK_PIECE);
     m_board[0][2] = new Bishop(2, 0, BLACK_PIECE);
     m_board[0][3] = new Queen (3, 0, BLACK_PIECE);
     m_board[0][4] = new King  (4, 0, BLACK_PIECE);
     m_board[0][5] = new Bishop(5, 0, BLACK_PIECE);
     m_board[0][6] = new Knight(6, 0, BLACK_PIECE);
     m_board[0][7] = new Rook  (7, 0, BLACK_PIECE);
     for(int i = 0; i < 8; i++){
         m_board[1][i] = new Pawn(i, 1, BLACK_PIECE);
     }
     for(int j = 0; j < 2; j++){
         for(int i = 0; i < 8; i++){
             m_listOfBlackPieces.push_back(m_board[j][i]);
         }
     }  
    
    for (int i = 0; i < 8; i++){
        m_board[6][i] = new Pawn(i, 6, WHITE_PIECE);
    }
    m_board[7][0] = new Rook  (0, 7, WHITE_PIECE);
    m_board[7][1] = new Knight(1, 7, WHITE_PIECE);
    m_board[7][2] = new Bishop(2, 7, WHITE_PIECE);
    m_board[7][3] = new Queen (3, 7, WHITE_PIECE);
    m_board[7][4] = new King  (4, 7, WHITE_PIECE);
    m_board[7][5] = new Bishop(5, 7, WHITE_PIECE);
    m_board[7][6] = new Knight(6, 7, WHITE_PIECE);
    m_board[7][7] = new Rook  (7, 7, WHITE_PIECE);

    for(int j = 7; j > 5; j--){
        for(int i = 0; i < 8; i++){
            m_listOfWhitePieces.push_back(m_board[j][i]);
        }
    }
     m_listOfSnapshots.push_back(snapshot());
 }


std::string ChessBoard::printBoard() const{
    std::string buf;
    char row = '8';
    for(int j = 0; j < 8; j++){
        buf  += row;
        buf  += ' ';
        row--;
        for(int i = 0; i < 8; i++){
            Position pos(i,j);
            Piece* p = at(pos);
            if(p != nullptr) {
                buf += p->print();
            } else {
                buf += ' ';
            }
        }
        buf += '\n';
    }
    buf += "        ";
    buf += '\n';
    buf += "  ";
    char col = 'A';
    for (int i = 0; i < 8; i++){
        buf += col;
        col++;
    }
    buf += '\n';
    return buf;
 }

Piece* ChessBoard::at(const Position pos) const {
    int x = pos.getX();
    int y = pos.getY();
    return m_board[y][x];
}

Piece* ChessBoard::getKing(bool color){
    std::vector<Piece*>& listOfPieces = color ? m_listOfWhitePieces : m_listOfBlackPieces;
    Piece* king = nullptr;
    for(int i = 0; i < listOfPieces.size(); i++){
        Piece* piece = listOfPieces.at(i);
        if(piece->isKing()){
            king = piece;
            break;
        }
    }
    return king;
}


void ChessBoard::setPiece(Piece* p, Position pos){
    int x = pos.getX();
    int y = pos.getY();
    m_board[y][x] = p;
}

void ChessBoard::clearSnapshotList(){
    for(int i = 0; i < m_listOfSnapshots.size(); i++){
        delete m_listOfSnapshots.at(i);
    }
    m_listOfSnapshots.clear();
};

bool ChessBoard::getPieceColor(Position pos){  //per andrea per i controlli nel main.
    Piece* p = at(pos);
    if(p == nullptr){
        throw new InvalidPosition();
    }
    bool color = p->color();
    return color;
}

void ChessBoard::move(Position from, Position to){
    Piece* pieceToMove = at(from);
    if(!isOccupied(from)){
        throw new InvalidPosition();
    } else {
        m_movesWithoutCaptures++; //per default, poi se sto mangiando azzero il conteggio;
        int pawnTurn;
        if(pieceToMove->isPawn()){
            pawnTurn = ((Pawn*) pieceToMove)->getTurnMove();
            pieceToMove->setTurnMove(m_numOfTurns); 
        }
        else m_pawnsHaveNotMoved++;
        try{
            pieceToMove->move(to, *this);  //che aggiorna la posizione dentro alla pedina ma non il puntatore della scacchiera.
        } catch(InvalidPosition* e){
            pieceToMove->setTurnMove(pawnTurn);
            throw new InvalidPosition();
        }
        
        if(isOccupied(to)){  //se to è occupato allora mangio. movesWithoutCaptures = 0;
            Piece* toEliminate = at(to);
            capture(toEliminate);
            m_movesWithoutCaptures = 0;
            clearSnapshotList();
        }
        setPiece(pieceToMove,to);
        setPiece(nullptr,from);
        
    }
    if(pieceToMove->isPawn()) {
        clearSnapshotList();  //muovo il pawn, che non può tornare indietro, quindi non si ripeterà più una posizione già avuta.
        m_pawnsHaveNotMoved = 0;
    }
    m_listOfSnapshots.push_back(snapshot());
    m_numOfTurns++;
}

void ChessBoard::tryMove(Position from , Position to){
      if(isOccupied(to)){   //mangia
        capture(at(to));
        setPiece(nullptr,to);
      }
      Piece* pieceToMove = at(from);
      if(pieceToMove == nullptr){
          std::cout << "NO PIECE TO MOVE IN TRY MOVE" << std::endl;
          return ;
      }

      // Change piece
      pieceToMove->setPosition(to);

      // Change chessboard
      setPiece(pieceToMove,to);
      setPiece(nullptr,   from);
}

bool ChessBoard::isOccupied(const Position to){
    bool occupied = false;
    if(at(to) != nullptr){
        occupied = true;
    }
    return occupied;
}

void ChessBoard::capture(Piece* toEliminate){
    std::vector<Piece*>& listOfEnemies = toEliminate->color() ? m_listOfWhitePieces : m_listOfBlackPieces;
    int i;
    for( i = 0; i < listOfEnemies.size(); i++){
        Piece* enemy = listOfEnemies.at(i);
        if(enemy == toEliminate){
            if(m_allowRecursion){
                std::string color = toEliminate->color() ? "white" : "black";
                std::cout << "Captured " << toEliminate->print() << ", of color " << color << std::endl;
            }
            delete toEliminate;
            m_numOfPieces--;
            listOfEnemies.erase(listOfEnemies.begin()+i);
            return;
        }
    }
}

ChessBoard* ChessBoard::snapshot(){
    ChessBoard* copyOfBoardPTR = new ChessBoard();
    for(int i = 0; i < 8;i++){
        for (int j = 0; j < 8; j++){
            Piece* piece = m_board[i][j];
            Position pos(i,j);
            copyOfBoardPTR->setPiece( piece, pos );  // faccio una copia del chessboard.
        }
    }
    return copyOfBoardPTR;
}

bool ChessBoard::operator==(const ChessBoard& cb) const {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Position pos(i,j);
            Piece* thisPiecePtr =    m_board[i][j];
            Piece* thatPiecePtr = cb.m_board[i][j];
            if ( (thisPiecePtr == nullptr) && (thatPiecePtr != nullptr ) ) return false;
            if ( (thisPiecePtr != nullptr) && (thatPiecePtr == nullptr ) ) return false;
            if ( thisPiecePtr != nullptr ) {
                if ( *thisPiecePtr != *thatPiecePtr ) {
                  return false;
                }
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const ChessBoard& cb){
    os << cb.printBoard();
    return os;
}

std::vector<Piece*>& ChessBoard::piecesThatThreaten(Piece* king, std::vector<Piece*>& listOfThreats){
    std::vector<Piece*>& listOfEnemies = king->color() ? m_listOfBlackPieces : m_listOfWhitePieces;
    Position kingsPosition = king->getPosition();
    for(int i = 0; i < listOfEnemies.size(); i++ ){
        Piece* enemy = listOfEnemies.at(i);
        //if(m_allowRecursion){
            enemy->makePossiblePositions(*this);
        //}
        std::vector<Position> possiblePositionsOfEnemy = enemy->getPossiblePositions();
        for(int j = 0; j < possiblePositionsOfEnemy.size(); j++){
            Position enemyPossibleMove = possiblePositionsOfEnemy.at(j);
            if( enemyPossibleMove == kingsPosition){
                listOfThreats.push_back(enemy);
            }
        }
    }
    return listOfThreats;
}

bool ChessBoard::enemyKingIsClose(Position pos, bool color){
    int x = pos.getX();
    int y = pos.getY();
    std::vector<Position> listOfSurroundingPositions;
    Position delta1(-1,  0);
    Position delta2(-1,  1);
    Position delta3(-1 ,-1);
    Position delta4( 0 , 1);
    Position delta5( 0 ,-1);
    Position delta6( 1, -1);
    Position delta7( 1,  0);
    Position delta8( 1,  1);
    listOfSurroundingPositions.push_back(delta1);
    listOfSurroundingPositions.push_back(delta2);
    listOfSurroundingPositions.push_back(delta3);
    listOfSurroundingPositions.push_back(delta4);
    listOfSurroundingPositions.push_back(delta5);
    listOfSurroundingPositions.push_back(delta6);
    listOfSurroundingPositions.push_back(delta7);
    listOfSurroundingPositions.push_back(delta8);
       
    for (int i = 0; i < listOfSurroundingPositions.size(); i++){
        Position nextToPosition = pos.addPosition(listOfSurroundingPositions.at(i));
        int x = nextToPosition.getX();
        int y = nextToPosition.getY();
        if( x < 0 || x > 7){
            continue;
        }
        if( y < 0 || y > 7){
            continue;
        }
        Piece* piecePTR = at(nextToPosition);
        if( piecePTR != nullptr ){
            if( piecePTR->isKing() && ( piecePTR->color() != color )){
                return true;
            }
        }
    }
    return false;
}

std::vector<Piece*>& ChessBoard::remainingPieces(std::vector<Piece*>& listOfRemainingPieces){
    for(int i = 0; i < m_listOfWhitePieces.size(); i++){
        Piece* piecePTR = m_listOfWhitePieces.at(i);
        if(piecePTR->isKing()){
            continue;
        }
        else {
            listOfRemainingPieces.push_back(piecePTR);
        }
    }
    for(int j = 0; j < m_listOfBlackPieces.size(); j++){
        Piece* piecePTR = m_listOfBlackPieces.at(j);
        if(piecePTR->isKing()){
            continue;
        }
        else {
            listOfRemainingPieces.push_back(piecePTR);
        }
    }
    return listOfRemainingPieces;
}


bool ChessBoard::canBeEaten(bool color, const Position& pos){
    std::vector<Piece*>& listOfEnemies = color ? m_listOfBlackPieces : m_listOfWhitePieces;
    for(int i = 0; i < listOfEnemies.size(); i++ ){
        Piece* enemy = listOfEnemies.at(i);
        if(enemy->isKing()){  //controlla se sto andando nelle 8 posizioni circostanti al re avversario!!!!!
            /*if(enemyKingIsClose(pos, color)){
                return true;
            }*/
            continue; //skippo il king avversario
        }
        enemy->makePossiblePositions(*this); //penso serva per avere sempre le posizioni aggiornate all'ultima mossa
        std::vector<Position> possiblePositionsOfEnemy = enemy->getPossiblePositions();
        Position enemyPossibleMove;
        for(int j = 0; j < possiblePositionsOfEnemy.size(); j++){
            Position enemyPossibleMove = possiblePositionsOfEnemy.at(j);
            if(enemy->isPawn()){
                if(pos.getX() == enemy->getX()){   //ignora le posizioni davanti ai pawn.
                    continue;
                }
                int diagonal_y = enemy->color() ? enemy->getY() - 1 : enemy->getY() + 1;
                int x1 = -1;
                int x2 = -1;
                if(diagonal_y - pos.getY() == 0){
                    if(enemy->getX() < 7 && enemy->getX() > 0){
                        x1 = enemy->getX() + 1;
                        x2 = enemy->getX() - 1;
                    } else if(enemy->getX() == 0){
                        x1 = enemy->getX() + 1;
                    } else {
                        x1 = enemy->getX() - 1;
                    }
                    if(pos.getX() == x1 || pos.getX() == x2){
                        return true;   //il pedone puo' mangiare in diagonale.
                    }
                }
            }
            if( enemyPossibleMove == pos){
                return true;
            }
        }
    }
    return false;
}

int signOfInt( int n ) {
    if ( n > 0 ) return  1;
    if ( n < 0 ) return -1;
    return 0;
}

bool ChessBoard::canBeCovered( Piece* king, std::vector<Piece*>& listOfThreats ){
    if( listOfThreats.size() != 1 ){  //either zero threaths or more than one: in which case not coverable in a single move.
        return false;
    }
    Piece* onlyThreat = listOfThreats.at(0);
    if(onlyThreat->isKnight()) {  //non si puo' coprire il re da un cavallo.
        return false;
    }
    bool canCoverKing = false;
    Position posOfThreat = onlyThreat->getPosition();
    Position kingsPosition = king->getPosition();
    int x = kingsPosition.getX();
    int y = kingsPosition.getY();
    int deltaX = signOfInt( posOfThreat.getX() - x );
    int deltaY = signOfInt( posOfThreat.getY() - y );
    Position velocity( deltaX, deltaY );
    Position toCover( x, y );
    bool color = king->color();
    std::vector<Piece*> listOfFriends = color ? m_listOfWhitePieces : m_listOfBlackPieces;
    while( canCoverKing == false && !(toCover == posOfThreat) ) {
        toCover.addPosition(velocity); // somma le due x e le due y
        for(int i = 0; i < listOfFriends.size() && canCoverKing == false; i++){
            Piece* aFriend = listOfFriends.at(i);
            if( aFriend == king ){
                continue;     //ignora il king.
            }
            if(m_allowRecursion){
                aFriend->makePossiblePositions(*this);
            }
            std::vector<Position> possibilePositions = aFriend->getPossiblePositions();
            for(int j = 0; j < possibilePositions.size(); j++){
                Position pos = possibilePositions.at(j);
                Position friendsPos(aFriend->getX(), aFriend->getY());
                if(pos == toCover){
                    ChessBoard tryChessBoard(*this);
                    tryChessBoard.tryMove(friendsPos, toCover);
                    Piece* tryKing = tryChessBoard.getKing(color);
                    std::vector<Piece*> newListOfThreats;
                    tryChessBoard.piecesThatThreaten( tryKing, newListOfThreats );
                    if(newListOfThreats.size() > 0){
                        continue;
                    }else {
                        canCoverKing = true;
                        m_listOfPriorityMoves.push_back(friendsPos); //pusho il from che sarà sempre pari.
                        m_listOfPriorityMoves.push_back(toCover);    //il to avra' sempre indice dispari.
                    }
                }
            }
        }
    }
    return canCoverKing;
}

bool ChessBoard::canEatThreat( Piece* king, std::vector<Piece*>& listOfThreats){
    if(listOfThreats.size() > 1){  //allora non è possibile mangiare tutti i pezzi in una singola mossa.
        return false;
    }
    bool canSaveTheKing = false;
    if(listOfThreats.size() == 1){
        Piece* onlyThreat = listOfThreats.at(0);
        Position posOfThreat = onlyThreat->getPosition();
        bool color = king->color();
        std::vector<Piece*> listOfFriends = color ? m_listOfWhitePieces : m_listOfBlackPieces;
        for(int i = 0; i < listOfFriends.size(); i++){
            Piece* aFriend = listOfFriends.at(i);
            if( aFriend == king ){
                continue;     //ignora il king.
            }
            if(m_allowRecursion){
                aFriend->makePossiblePositions(*this);
            }
            std::vector<Position> possiblePositions = aFriend->getPossiblePositions();
            for(int j = 0; j < possiblePositions.size(); j++){
                Position pos = possiblePositions.at(j);
                Position friendsPos(aFriend->getX(), aFriend->getY());
                if(pos == posOfThreat){
                    ChessBoard tryChessBoard(*this);
                    tryChessBoard.tryMove(friendsPos, posOfThreat);
                    Piece* tryKing = tryChessBoard.getKing(color);
                    std::vector<Piece*> newListOfThreats;
                    tryChessBoard.piecesThatThreaten( tryKing, newListOfThreats );
                    if(newListOfThreats.size() > 0){
                        continue;
                    }else {
                        canSaveTheKing = true;
                        m_listOfPriorityMoves.push_back(friendsPos); //pusho il from che sarà sempre pari.
                        m_listOfPriorityMoves.push_back(posOfThreat); //il to avra' sempre indice dispari.
                    }
                }
            }
        }
    }
    return canSaveTheKing;
}

bool ChessBoard::canEscape(Piece* king){
    bool canEscape = false;
    Position initialPosition = king->getPosition();
    king->makePossiblePositions(*this);
    std::vector<Position> kingsPossiblePositions = king->getPossiblePositions();
    for(int i = 0; i < kingsPossiblePositions.size(); i++){
        Position pos = kingsPossiblePositions.at(i);
        ChessBoard tryChessBoard(*this);            //lo devo mettere dentro al for, cosi' si rinnova ogni volta
        tryChessBoard.tryMove(initialPosition, pos);
        std::vector<Piece*> newListOfThreats;
        Piece* tryKing = tryChessBoard.getKing(king->color());
        tryChessBoard.piecesThatThreaten( tryKing, newListOfThreats );
        if( newListOfThreats.size() > 0 ){
            continue;
        }
        canEscape =  true;
        m_listOfPriorityMoves.push_back(initialPosition);  //il from.
        m_listOfPriorityMoves.push_back(pos);              //il to.
    }
    return canEscape;
}

bool ChessBoard::isCheck(Piece* king){
    bool isCheck = false;
    std::vector<Piece*> listOfThreats;
    piecesThatThreaten(king, listOfThreats);
    if(listOfThreats.size() != 0){   //c'è qualcuno che può mangiare il re.
        isCheck = true;
        if(m_allowRecursion){
            std::string color = king->color() ? "white" : "black";
            bool b1 = canEatThreat(king, listOfThreats);
            bool b2 = canBeCovered(king, listOfThreats);
            bool b3 = canEscape(king);
        }
    }
    return isCheck;
}


bool ChessBoard::isCheckMate(Piece* king){
    if(!isCheck(king)){   //nessuno sta per mangiare il re.
        return false;
    }
    //il re è sotto scacco
    std::vector<Piece*> listOfThreats;
    piecesThatThreaten(king, listOfThreats);
    bool b1 = canBeCovered(king, listOfThreats);   //puo' venire coperto?
    bool b2 = canEatThreat(king, listOfThreats);   //puo' venire mangiato il pezzo che minaccia?
    if( b1 || b2 ) {
        return false;
    }
    bool checkMate = true;
    if(m_allowRecursion){
        Position initialPosition = king->getPosition();
        king->makePossiblePositions(*this);
        std::vector<Position> kingsPossiblePositions = king->getPossiblePositions();
        for(int i = 0; i < kingsPossiblePositions.size() && checkMate == true; i++){
            Position pos = kingsPossiblePositions.at(i);
            ChessBoard tryChessBoard(*this);
            tryChessBoard.tryMove(initialPosition, pos);
            std::vector<Piece*> newListOfThreats;
            Piece* tryKing = tryChessBoard.getKing(king->color());
            tryChessBoard.piecesThatThreaten( tryKing, newListOfThreats );//se non può muoversi allora è checkMate.
            if( newListOfThreats.size() == 0 ){
                checkMate =  false;
                m_listOfPriorityMoves.push_back(initialPosition);  //il from.
                m_listOfPriorityMoves.push_back(pos);              //il to.
            }
        }
    }
    return checkMate;
}

bool ChessBoard::isStalemate(Piece* king){ //controllo della situazione di stallo.
    if(isCheck(king)){
        return false;
    }
    
    //il re non è sotto scacco
    bool color = king->color();
    std::vector<Piece*> listOfFriends = king->color() ? m_listOfWhitePieces : m_listOfBlackPieces;
    for(int i = 0; i < listOfFriends.size(); i++){
        Piece* aFriend = listOfFriends.at(i);
        Position initialPosition = aFriend->getPosition();
        if(m_allowRecursion){
            aFriend->makePossiblePositions(*this);
        }
        std::vector<Position> friendsPossiblePositions = aFriend->getPossiblePositions();
        for(int i = 0; i < friendsPossiblePositions.size(); i++){
            Position pos = friendsPossiblePositions.at(i);
            ChessBoard tryChessBoard(*this);
            tryChessBoard.tryMove(initialPosition, pos);
            Piece* tryKing = tryChessBoard.getKing(color);
            std::vector<Piece*> listOfThreats;
            piecesThatThreaten(tryKing, listOfThreats);
            if(listOfThreats.size() == 0){  //se c'è un pezzo che può muoversi legalmente senza scoprire il king allora non è patta;
                return false;
            }
        }
    }
    std::cout << "Stopped due to staleMate" << std::endl;
    return true;
}

bool ChessBoard::fiftyMoveRule(){
    if(m_movesWithoutCaptures == 50 || m_pawnsHaveNotMoved == 50){
        std::cout << "Stopped due to 50 move rule " << std::endl;
        return true;
    }
    return false;
}

bool ChessBoard::thirdRepetition(){  //si fa sull'ultimo snapshot che è stato pushed dentro alla lista, suppondendo che sia già stato fatto e trovato falso per tutte le positions prima di questa.
    bool isThirdRepetition = false;
    int count = 0;
    ChessBoard* last = m_listOfSnapshots.back();
    for(int i = 0; i < m_listOfSnapshots.size() - 1; i++){
        if(*m_listOfSnapshots.at(i) == *last){
            count ++;
            if(count == 3){
                std::cout << "Stopped due to third repetition" << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::isDeadPosition(){
    if(m_numOfPieces == 2){    //allora rimangono solo i due re.
        std::cout << "Only two kings left on board. DEAD POSITION" << std::endl;
        std::cout << "Stopped due to dead position" << std::endl;
        return true;
    } else if(m_numOfPieces == 3){   //allora sono rimasti i due re e un altro pezzo.
        int whitePieces = m_listOfWhitePieces.size();
        std::vector<Piece*>& aList = (whitePieces == 1) ? m_listOfBlackPieces : m_listOfWhitePieces;
        Piece* notAKing = nullptr;
        for(int i = 0; i < aList.size(); i++){
            if(aList.at(i)->isKing()){
                continue;
            }
            notAKing = aList.at(i);
            break;
        }
        if(notAKing->isKnight() || notAKing->isBishop()){
            std::string pieceType = notAKing->isKnight() ? "knight" : "bishop";
            std::cout << "Only two kings and a " << pieceType << " left on board. DEAD POSITION" << std::endl;
            std::cout << "Stopped due to dead position" << std::endl;
            return true;
        }
    } else if(m_numOfPieces == 4){   //servirebbe startingPosition di Bishop
        std::vector<Piece*> listOfRemainingPieces;
        remainingPieces(listOfRemainingPieces);
        Piece* piece1PTR = listOfRemainingPieces.at(0);
        Piece* piece2PTR = listOfRemainingPieces.at(1);
        if(piece1PTR->color() != piece2PTR->color()){
            if(piece1PTR->isBishop() && piece2PTR->isBishop()){  //serve controllare se avevano starting x diverse tra di loro.
                int x1 = ((Bishop*)piece1PTR) ->getFirstX();
                int x2 = ((Bishop*)piece2PTR) ->getFirstX();
                if(x1 != x2){
                    std::cout << "Only two kings and two bishops that started on the same color square left on board. DEAD POSITION" << std::endl;
                    std::cout << "Stopped due to dead position" << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isTie(Piece* king){
    bool staleMate = isStalemate(king);
    bool fiftyMoves= fiftyMoveRule();
    bool thirdRep  = thirdRepetition();
    bool deadPos   = isDeadPosition();
    if(staleMate || fiftyMoves || thirdRep || deadPos){
        return true;
    }
    return false;
}

void ChessBoard::promotion(Piece* pawn, Piece* choiceOfPromotion){
        Position posOfPawn = pawn->getPosition();
        choiceOfPromotion->setPosition(posOfPawn);
        std::vector<Piece*>& listOfFriends = pawn->color() ? m_listOfWhitePieces : m_listOfBlackPieces;
        for(int i = 0; i < listOfFriends.size(); i++){
            if(pawn == listOfFriends.at(i)){
                listOfFriends.at(i) = choiceOfPromotion;
                listOfFriends.push_back( choiceOfPromotion );
                listOfFriends.erase( listOfFriends.begin()+i );
            }
        }
        delete pawn;
        setPiece(choiceOfPromotion, posOfPawn);
        m_listOfSnapshots.push_back(snapshot());
}
