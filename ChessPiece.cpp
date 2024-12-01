#include "ChessGame.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include <iostream>

using namespace std;

ChessPiece::ChessPiece(Colour pieceColour, Name pieceName) : 
	pieceColour(pieceColour), pieceName(pieceName) {};

// Chess Piece destructor
ChessPiece::~ChessPiece() {};

//Overloading of ostream for ChessPiece pointers
ostream& operator << (std::ostream& os, ChessPiece* cp) {
	if (cp != nullptr) {
		cp->printPiece(os);
	}
	else {
		os << ". ";
	}
	return os;
}



