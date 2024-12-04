#include "ChessPiece.h"
#include "King.h"
#include <iostream>
#include <cstdlib> //for abs

using namespace std;

// King constructor - check is set to false by default; checked at start of each turn
King::King(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour,
		pieceName) {};

//King destructor, temporarily printing destructed messages to see memory mgmt
King::~King() {};

//King clone method
ChessPiece* King::clone() const {
	return new King(*this); //Using default copy constructor for King
}

void King::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "k ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "K ";
	}
};

bool King::isValidMove(char const move_from[2], char const move_to[2],
		ChessGame* cg, bool& isPieceTaken) {
	//first check if the king is being moved only one square
	if (!(
				((abs(move_from[0] - move_to[0]) == 1) && 
				(abs(move_from[1] - move_to[1]) < 2)) || 
				((abs(move_from[1] - move_to[1]) == 1) &&
				 (abs(move_from[0] - move_to[0]) < 2))
				)) {
		return false;
	}
	// if move_to is empty; valid move
	else if(!cg->getBoardPiece(move_to)) {
		return true; 
	}
	// if move_to occupied by an opposing piece; valid move
	else if (cg->capturesPiece(move_from, move_to)) {
		isPieceTaken = true; //Indicate piece being taken
		return true;
	}
	// else (e.g. if move_to occupied by your piece) invalid move
	return false;
}



