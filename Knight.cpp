#include "ChessPiece.h"
#include "Knight.h"
#include <iostream>
#include <cstdlib> //for abs function

using namespace std;

// Knight constructor
Knight::Knight(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour, 
		pieceName) {};

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

bool Knight::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg, bool& isPieceTaken) {
	//check to make sure that either it is moving 2 squares horizontally and 1
	//square vertically, or vice versa (no other combo is legal)
	if (!(((abs(move_from[0] - move_to[0]) == 2) && 
					(abs(move_from[1] - move_to[1]) == 1)) 
				|| ((abs(move_from[0] - move_to[0]) == 1) && 
					(abs(move_from[1] - move_to[1]) == 2)))
				) {
		/* If the above is not the case, update the isPieceTaken bool, to indicate 
		 * false - as even if there was an enemy piece in the move_to square, this 
		 * is an invalid move so no piece can be taken */
		isPieceTaken = false;
		return false;
	}
	// else we can return true, and let the isPieceTaken marker that has been
	// precomputed take care of whether the move_to square is empty or not
	else {
		return true; 
	}
}

