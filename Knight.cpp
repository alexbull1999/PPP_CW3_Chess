#include "ChessPiece.h"
#include "Knight.h"
#include <iostream>
#include <cstdlib> //for abs function

using namespace std;

// Knight constructor
Knight::Knight(Colour pieceColour) : ChessPiece(pieceColour) {};

//Knight destructor
Knight::~Knight() {};

//Knight clone method invoked in the ChessGame copy constructor
ChessPiece* Knight::clone() const {
	return new Knight(*this); //Using default copy constructor for Knight
}

void Knight::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "n ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "N ";
	}
};

//Getter for the piece name, returning a string literal
//representing the name of a piece
const char* Knight::getPieceName() const { return "Knight"; }

bool Knight::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg) {
	//check to make sure that either it is moving 2 squares horizontally and 1
	//square vertically, or vice versa (no other combo is legal)
	if (!(((abs(move_from[0] - move_to[0]) == 2) && 
					(abs(move_from[1] - move_to[1]) == 1)) 
				|| ((abs(move_from[0] - move_to[0]) == 1) && 
					(abs(move_from[1] - move_to[1]) == 2)))
				) {
		return false;
	}
	return true;
}

