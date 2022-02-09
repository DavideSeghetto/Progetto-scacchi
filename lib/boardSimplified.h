//SCRITTO DA BRUTTOMESSO ANDREA 

#ifndef BOARDSIMPLIFIED_H
#define BOARDSIMPLIFIED_H

#include <string>
#include <fstream>

class boardSimplified{
	
	private:
		//Di default si inizializza una matrice che farà da scacchiera
		//con i pezzi bianchi nel lato inferiore
		char board[8][8] =
       	{
			{'T','C','A','D','R','A','C','T'},
			{'P','P','P','P','P','P','P','P'},
			{' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' '},
			{'p','p','p','p','p','p','p','p'},
			{'t','c','a','d','r','a','c','t'},
		};
	public:
		//Non fa nulla, la scacchiera e' gia' riempita in maniera corretta
		//al momento della creazione della variabile d'esemplare.
		boardSimplified(){}

		// Overload dell'operator << come friend function al fine di stampare
		// la scacchiera in maniera piu' naturale.
		friend std::ostream& operator<<(std::ostream& os, boardSimplified b);

		// Funzione che muove i pezzi, accetta due stringhe in cui sono contenute
		// rispettivamente le coordinate del pezzo da spostare e la destinazione di tale pezzo
		// nel formato LetteraNumero. NON VIENE EFFETTUATA NESSUNA FORMA DI CONTROLLO POICHE'
		// SI ASSUME CHE LE MOSSE VENGANO DAL LOG DI UNA PARTITA REALMENTE AVVENUTA.
		void move(std::string start, std::string end);

		// Funzione che controlla se ci si trova in una situazione in cui sta per avvenire una 
		// promozione, accetta una stringa contente le coordinate della scacchiera in cui si trova 
		// il pezzo dopo essere stato mosso.
		// Ritorna TRUE se e solo se il pezzo e' un pedone e si trova in una delle due traverse
		// agli estremi della scacchiera.
		bool checkPromotion(std::string pos);

		// Funzione che ritorna il char corrispondente al pezzo situato nelle coordinate della scacchiera
		// fornite dalla stringa pos
		char pieceAt(std::string pos);

		// Funzione che promuove il pezzo alle coordinate della scacchiera fornite da pos nel pezzo p.
		// NON VIENE EFFETTUATA NESSUNA FORMA DI CONTROLLO POICHE' SI ASSUME CHE IL PEZZO P FORNITO
		// PROBENGA DAL LOG DI UNA PARTITA REALMENTE AVVENUTA E QUINDI CON UNA PROMOZIONE VALIDA.
		void promotion(std::string pos, char p);

		// Funzione che indica se si sta cercando di eseguire l'arrocco. Vengono fornite le coordinate
		// di partenza ed arrivo del pezzo da spostare. 
		// Ritorna TRUE se e solo se viene effettuata la mossa su un re il quale e 'nella sua posizione
		// originale mentre la destinazione si trova ad una differenza di due caselle sulla stessa traversa. 
		// NON VIENE EFFETTUATO ALTRO CONTROLLO POICHE' SI ASSUME CHE LE MOSSE VENGANO DAL LOG DI UNA PARTITA 
		// REALMENTE AVVENUTA.
		bool checkCastling(std::string start, std::string end);

		// Funzione che sposta la torre in modo tale da completare l'arrocco con il re che e' gia' stato
		// posizionato alle coordinate fornite da pos.
		// NON VIENE EFFETTUATO ALTRO CONTROLLO POICHE' SI ASSUME CHE LE MOSSE VENGANO DAL LOG DI UNA PARTITA 
		// REALMENTE AVVENUTA.
		void castling(std::string pos);
};

#endif

