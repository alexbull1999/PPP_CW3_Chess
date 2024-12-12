#include "ChessPiece.h"
#include "Bishop.h"
#include <iostream>
#include <cstdlib> //for abs() function

using namespace std;

// Bishop constructor
Bishop::Bishop(Colour pieceColour) : ChessPiece(pieceColour) {};

//Bishop destructor
Bishop::~Bishop() {};

//Bishop clone method invoked in the ChessGame copy constructor
ChessPiece* Bishop::clone() const {
	return new Bishop(*this); //Using default copy constructor for Bishop
}

void Bishop::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "b ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "B ";
	}
};

//Getter for the piece name, returning a string literal representing the name of a piece
const char* Bishop::getPieceName() const { return "Bishop"; }

bool Bishop::isValidMove(char const move_from[2], char const move_to[2],
		ChessGame* cg, bool& isPieceTaken) {
	return isValidBishopMove(move_from, move_to, cg, isPieceTaken);
}


