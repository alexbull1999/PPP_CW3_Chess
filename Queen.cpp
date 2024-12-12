#include "ChessPiece.h"
#include "Queen.h"
#include <iostream>
#include "Bishop.h"
#include "Rook.h"

using namespace std;

// Queen constructor now has to pass through Bishop and Rook constructors to 
// reach the ChessPiece constructor and initialise its pieceColour
Queen::Queen(Colour pieceColour) : ChessPiece(pieceColour) {};

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

//Getter for the piece name, returning a string literal representing
//the name of a piece
const char* Queen::getPieceName() const { return "Queen"; }

bool Queen::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg) {
	/*there should never be conflicts here, as from the Queen's position
	 * a move that is valid for a Bishop would not be valid for a Rook
	 * and vice-versa due to diagonal vs vertical/horizontal movement. */
	return isValidBishopMove(move_from, move_to, cg) ||
		isValidRookMove(move_from, move_to, cg);
}
