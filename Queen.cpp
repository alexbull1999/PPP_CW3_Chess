#include "ChessPiece.h"
#include "Queen.h"
#include <iostream>
#include "Bishop.h"
#include "Rook.h"

using namespace std;

// Queen constructor now has to pass through Bishop and Rook constructors to 
// reach the ChessPiece constructor and initialise its pieceColour
Queen::Queen(Colour pieceColour, Name pieceName) : 
	ChessPiece(pieceColour, pieceName),
	Bishop(pieceColour, pieceName), Rook(pieceColour, pieceName) {};

//Queen destructor
Queen::~Queen() {};

//Queen clone method invoked in the ChessGame copy constructor
ChessPiece* Queen::clone() const {
	return new Queen(*this); //Using default copy constructor for Queen
}

void Queen::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "q ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "Q ";
	}
};

bool Queen::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg, bool& isPieceTaken) {
	/*there should never be conflicts here, as from the Queen's position
	 * a move that is valid for a Bishop would not be valid for a Rook
	 * and vice-versa due to diagonal vs vertical/horizontal movement. */
	return Bishop::isValidMove(move_from, move_to, cg, isPieceTaken) ||
		Rook::isValidMove(move_from, move_to, cg, isPieceTaken);
}
